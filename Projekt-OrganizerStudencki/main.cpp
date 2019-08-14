#include "oknoglowne.h"
#include "oknologowania.h"
#include <QApplication>
#include <iostream>
#include <ctime>
#include "alarm.h"
#include "ocena.h"
#include "sqlite3.h"
#include <QMessageBox>
#include "profil.h"
#include <thread>
#include <mutex>
#include "zajecia.h"

void odczytczasu(bool& _przelacznik, std::mutex& _blokada, time_t& _czas, const std::shared_ptr<std::vector<alarm>> & _alarmy,
                 const std::shared_ptr<std::map<int,std::shared_ptr<wydarzenie>>> & _wydarzenia,
                 const std::shared_ptr<std::map<int,std::shared_ptr<zajecia>>> & _kontenerzajecia,
                 const std::shared_ptr<std::list<std::pair<std::string, std::string>>> & _listazdarzen)
{
    while (_przelacznik)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        _blokada.lock();
        _czas = time(NULL);
        //std::cout << ctime(&_czas) << std::endl;
        std::vector<alarm>::iterator italarm;
        for (italarm = _alarmy->begin(); italarm != _alarmy->end(); italarm++)
            if (_czas == (*italarm).dajdate())
            {
                std::string a = std::to_string((*italarm).dajdzwiek());
                a += " ";
                a += std::to_string((*italarm).dajglosnosc());
               _listazdarzen->push_front(std::pair<std::string, std::string>(typeid(*italarm).name(), a));
            }
        std::map<int,std::shared_ptr<wydarzenie>>::iterator itwyd;
        for (itwyd = _wydarzenia->begin(); itwyd != _wydarzenia->end(); itwyd++)
        {
            std::shared_ptr<wydarzenie> lok = std::get<1>(*itwyd);
            if (lok->dajdate() == _czas)
            {
                _listazdarzen->push_front(std::pair<std::string, std::string>(typeid(*(lok.get())).name(), lok->dajnazwe()));
            }
        }
        std::map<int,std::shared_ptr<zajecia>>::iterator itzaj;
        for (itzaj = _kontenerzajecia->begin(); itzaj != _kontenerzajecia->end(); itzaj++)
        {
            std::shared_ptr<zajecia> lok = std::get<1>(*itzaj);
            std::vector<time_t> pom = lok->dajdaty();
            for (int i = 0; i < pom.size(); i++)
                if (pom[i] == _czas)
                {
                    _listazdarzen->push_front(std::pair<std::string, std::string>(typeid(*(lok.get())).name(), lok->dajprzedm()->dajnazwe()));
                }
        }
        _blokada.unlock();
    }
}

int main(int argc, char *argv[])
{
    //kontenery zdarzen
    std::shared_ptr<std::vector<alarm>> alarmy(new std::vector<alarm>);
    std::shared_ptr<std::map<int,std::shared_ptr<zajecia>>> kontenerzajecia(new std::map<int,std::shared_ptr<zajecia>>);
    std::shared_ptr<std::map<int,std::shared_ptr<wydarzenie>>> wydarzenia(new std::map<int,std::shared_ptr<wydarzenie>>);
    std::shared_ptr<std::list<std::pair<std::string, std::string>>> listazdarzen(new std::list<std::pair<std::string, std::string>>);
    //obslugaczasu - watek
    bool a1 = true;
    std::mutex blokada;
    time_t czas;
    std::thread czassystemowy(odczytczasu, std::ref(a1), std::ref(blokada), std::ref(czas), std::ref(alarmy)
                              , std::ref(wydarzenia), std::ref(kontenerzajecia), std::ref(listazdarzen));
    czassystemowy.detach();
    //obsługa czasu end
    QApplication a(argc, argv); //aplikacja - inicjalizacja
    int nrprofilu = 0;
    OknoLogowania l(&nrprofilu); //logowanie
    l.show();
    a.exec();

    if (nrprofilu != 0) //jak sie zalogujemy to uruchom okno glowne
    {

        OknoGlowne c(alarmy, wydarzenia, kontenerzajecia, nrprofilu, listazdarzen);
        c.show();
        a.exec();
    }
    return 0;
}

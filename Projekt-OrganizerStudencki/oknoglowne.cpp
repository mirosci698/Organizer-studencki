#include "oknoglowne.h"
#include "ui_oknoglowne.h"
#include "oknoalarmu.h"
#include <QTextCodec>
#include <clocale>
#include <thread>
#include <string>
#include <sstream>
#include <fstream>
#include <Windows.h>
#define PLIKWEJ "przedmioty.txt"
OknoGlowne::OknoGlowne(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OknoGlowne)
{
    ui->setupUi(this);
    //dodawanie miesięcy
    wykonajkalendarz();
}
void OknoGlowne::sprawdzanie(bool &przel)
{
    while (przel)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        emit ui->pushButton->clicked();
    }
}
OknoGlowne::OknoGlowne(const std::shared_ptr<std::vector<alarm>>& _alarmy,
                       const std::shared_ptr<std::map<int,std::shared_ptr<wydarzenie>>>& wydarzenia,
                       const std::shared_ptr<std::map<int,std::shared_ptr<zajecia>>> & zajecia, int _nrprofilu,
                       const std::shared_ptr<std::list<std::pair<std::string, std::string>>>& _listazdarzen):
    QMainWindow(NULL),
    ui(new Ui::OknoGlowne)
{
    ui->setupUi(this);
    nrprofilu = _nrprofilu;
    listazdarzen = _listazdarzen;
    //-------------------------------
    przel = true;
    std::thread spr(&OknoGlowne::sprawdzanie, this, std::ref(przel));
    spr.detach();
    //--------------------------
    wektoralarmow =_alarmy;
    mapaprzedmiotow.reset(new std::map<int,std::shared_ptr<przedmiot>>);
    mapazajec=zajecia;
    mapawydarzen = wydarzenia;
    mapaocen.reset(new std::map<int,std::shared_ptr<ocena>>);
    wczytaniealarmow();
    wczytanieprzedmiotow();
    wczytaniewydarzen();
    wczytaniezajec();
    wczytanieocen();
    wykonajkalendarz();
    widok();
}
void OknoGlowne::wczytaniealarmow()
{
    std::stringstream ss;
    ss << nrprofilu;
    nazwaplikualarmow = ss.str();
    nazwaplikualarmow += "-alarmy.txt";
    std::fstream plikwej;
    plikwej.open(nazwaplikualarmow, std::ios::in);
    if (!plikwej.is_open())
    {
        std::ofstream plikwyj;
        plikwyj.open(nazwaplikualarmow, std::ios::out);
        if (!plikwyj.is_open())
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Błąd. Nie udało się poprawnie otworzyć pliku alarmów. Wyłącz program i spróbuj ponownie");
            okienko->show();
        }
        plikwyj.close();
    }
    else
    {
        time_t lokczas;
        int lokdzwiek;
        int lokglosnosc;
        while (!plikwej.eof())
        {
            plikwej >> lokczas;
            if(plikwej.eof())
                break;      //zawsze wczytuje jakas wartosc nawet przy pustym dlatego break
            plikwej >> lokdzwiek;
            plikwej >> lokglosnosc;
            try {
                wektoralarmow->push_back(alarm(lokczas, lokdzwiek, lokglosnosc));
            }
            catch (std::logic_error)
            {

                continue;
            }
            catch (std::exception)
            {
                okienko.reset(new QMessageBox);
                okienko->setText("Błąd. Nie udało się wczytać alarmów. Wyłącz program i spróbuj ponownie.");
                okienko->show();
            }
        }
        plikwej.close();
    }
}
void OknoGlowne::wczytanieprzedmiotow()
{
    numeratorprzedm = 0;
    std::fstream plikwej;
    plikwej.open(PLIKWEJ, std::ios::in);
    if (!plikwej.is_open())
    {
        std::ofstream plikwyj;
        plikwyj.open(PLIKWEJ, std::ios::out);
        if (!plikwyj.is_open())
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Błąd. Nie udało się poprawnie otworzyć pliku przedmiotów. Wyłącz program i spróbuj ponownie");
            okienko->show();
        }
        plikwyj.close();
    }
    else
    {
        std::string loknazwa;
        std::string loknazwisko;
        std::string lokimie;
        int lokECTS;
        std::string lokuwagi;
        int lokID;
        while (!plikwej.eof())
        {
            plikwej >> lokID;
            if(plikwej.eof())
                break;      //zawsze wczytuje jakas wartosc nawet przy pustym dlatego break
            plikwej >> loknazwa;
            plikwej >> loknazwisko;
            plikwej >> lokimie;
            plikwej >> lokECTS;
            plikwej >> lokuwagi;
            if (lokuwagi == "<puste>")
                    lokuwagi = "";
            try {
                mapaprzedmiotow->insert(std::pair<int, std::shared_ptr<przedmiot>>(lokID, std::shared_ptr<przedmiot>(new przedmiot(loknazwa, loknazwisko, lokimie, lokECTS, lokuwagi))));
            }
            catch (std::exception)
            {
                okienko.reset(new QMessageBox);
                okienko->setText("Błąd. Nie udało się wczytać przedmiotów. Wyłącz program i spróbuj ponownie.");
                okienko->show();
            }
        }
        if (mapaprzedmiotow->size() > 0)
            numeratorprzedm = std::get<0>(*(mapaprzedmiotow->rbegin()));
        else
            numeratorprzedm = 0;
        plikwej.close();
    }
}
void OknoGlowne::wczytaniewydarzen()
{
    numeratorwyd = 0;
    std::stringstream ss;
    ss << nrprofilu;
    nazwaplikuwydarzen = ss.str();
    nazwaplikuwydarzen += "-wydarzenia.txt";
    std::fstream plikwej;
    plikwej.open(nazwaplikuwydarzen, std::ios::in);
    if (!plikwej.is_open())
    {
        std::ofstream plikwyj;
        plikwyj.open(nazwaplikuwydarzen, std::ios::out);
        if (!plikwyj.is_open())
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Błąd. Nie udało się poprawnie otworzyć pliku wydarzeń. Wyłącz program i spróbuj ponownie");
            okienko->show();
        }
        plikwyj.close();
    }
    else
    {
        int lokID;
        time_t lokczas;
        std::string loknazwa;
        std::string lokklasa;
        int lokIDprzed;
        std::string lokopis;
        while (!plikwej.eof())
        {
            plikwej >> lokID;
            if(plikwej.eof())
                break;      //zawsze wczytuje jakas wartosc nawet przy pustym dlatego break
            plikwej >> lokczas;
            plikwej >> loknazwa;
            plikwej >> lokklasa;
            plikwej >> lokIDprzed;
            plikwej >> lokopis;
            if (lokopis == "<pusty>")
                lokopis = "";
            try {
                if (lokklasa == "kartkowka")
                {
                    mapawydarzen->insert(std::pair<int, std::shared_ptr<wydarzenie>>(lokID,
                    std::shared_ptr<wydarzenie>(new kartkowka(lokczas, loknazwa, lokopis,
                    mapaprzedmiotow->at(lokIDprzed).get()))));
                } else if (lokklasa == "kolokwium")
                {
                    mapawydarzen->insert(std::pair<int, std::shared_ptr<wydarzenie>>(lokID,
                    std::shared_ptr<wydarzenie>(new kolokwium(lokczas, loknazwa, lokopis,
                    mapaprzedmiotow->at(lokIDprzed).get()))));
                } else if (lokklasa == "egzamin")
                {
                    mapawydarzen->insert(std::pair<int, std::shared_ptr<wydarzenie>>(lokID,
                    std::shared_ptr<wydarzenie>(new egzamin(lokczas, loknazwa, lokopis,
                    mapaprzedmiotow->at(lokIDprzed).get()))));
                } else if (lokklasa == "inne")
                {
                    mapawydarzen->insert(std::pair<int, std::shared_ptr<wydarzenie>>(lokID,
                    std::shared_ptr<wydarzenie>(new inne(lokczas, loknazwa, lokopis))));
                }
            }
            catch (std::logic_error)
            {

                continue;
            }
            catch (std::exception)
            {
                okienko.reset(new QMessageBox);
                okienko->setText("Błąd. Nie udało się wczytać wydarzeń. Wyłącz program i spróbuj ponownie.");
                okienko->show();
            }
        }
        plikwej.close();
    }
    if (mapawydarzen->size() > 0)
        numeratorwyd = std::get<0>(*mapawydarzen->rbegin());
    else
        numeratorwyd = 0;
}
void OknoGlowne::wczytaniezajec()
{
    numeratorzaj = 0;
    std::stringstream ss;
    ss << nrprofilu;
    nazwaplikuzaj = ss.str();
    nazwaplikuzaj += "-zajecia.txt";
    std::fstream plikwej;
    plikwej.open(nazwaplikuzaj, std::ios::in);
    if (!plikwej.is_open())
    {
        std::ofstream plikwyj;
        plikwyj.open(nazwaplikuzaj, std::ios::out);
        if (!plikwyj.is_open())
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Błąd. Nie udało się poprawnie otworzyć pliku wydarzeń. Wyłącz program i spróbuj ponownie");
            okienko->show();
        }
        plikwyj.close();
    }
    else
    {
        std::vector<time_t> daty;
        int lokID;
        std::string lokklasa;
        int lokIDprzed;
        int lokil;
        while (!plikwej.eof())
        {
            plikwej >> lokID;
            if(plikwej.eof())
                break;      //zawsze wczytuje jakas wartosc nawet przy pustym dlatego break
            plikwej >> lokklasa;
            plikwej >> lokIDprzed;
            plikwej >> lokil;
            for (int i = 0; i < lokil; i++)
            {
                time_t data;
                plikwej >> data;
                daty.push_back(data);
            }
            try {
                if (lokklasa == "wyklad")
                {
                    mapazajec->insert(std::pair<int, std::shared_ptr<zajecia>>(lokID,
                    std::shared_ptr<zajecia>(new wyklad(mapaprzedmiotow->at(lokIDprzed).get()))));
                    mapazajec->at(lokID)->wpiszdaty(daty);
                } else if (lokklasa == "cwiczenia")
                {
                    mapazajec->insert(std::pair<int, std::shared_ptr<zajecia>>(lokID,
                    std::shared_ptr<zajecia>(new cwiczenia(mapaprzedmiotow->at(lokIDprzed).get()))));
                    mapazajec->at(lokID)->wpiszdaty(daty);
                } else if (lokklasa == "laboratorium")
                {
                    mapazajec->insert(std::pair<int, std::shared_ptr<zajecia>>(lokID,
                    std::shared_ptr<zajecia>(new laboratorium(mapaprzedmiotow->at(lokIDprzed).get()))));
                    mapazajec->at(lokID)->wpiszdaty(daty);
                } else if (lokklasa == "projekt")
                {
                    mapazajec->insert(std::pair<int, std::shared_ptr<zajecia>>(lokID,
                    std::shared_ptr<zajecia>(new projekt(mapaprzedmiotow->at(lokIDprzed).get()))));
                    mapazajec->at(lokID)->wpiszdaty(daty);
                } else if (lokklasa == "seminarium")
                {
                    mapazajec->insert(std::pair<int, std::shared_ptr<zajecia>>(lokID,
                    std::shared_ptr<zajecia>(new seminarium(mapaprzedmiotow->at(lokIDprzed).get()))));
                    mapazajec->at(lokID)->wpiszdaty(daty);
                } else if (lokklasa == "praktyka")
                {
                    mapazajec->insert(std::pair<int, std::shared_ptr<zajecia>>(lokID,
                    std::shared_ptr<zajecia>(new praktyka(mapaprzedmiotow->at(lokIDprzed).get()))));
                    mapazajec->at(lokID)->wpiszdaty(daty);
                }
            }

            catch (std::exception)
            {
                okienko.reset(new QMessageBox);
                okienko->setText("Błąd. Nie udało się wczytać wydarzeń. Wyłącz program i spróbuj ponownie.");
                okienko->show();
            }
            for (int i = 0; i < daty.size(); i++)
                daty.pop_back();
        }
        plikwej.close();
    }
    if (mapazajec->size() > 0)
        numeratorzaj = std::get<0>(*mapazajec->rbegin());
    else
        numeratorzaj = 0;
}
void OknoGlowne::wczytanieocen()
{
    numeratorocen = 0;
    std::stringstream ss;
    ss << nrprofilu;
    nazwaplikuocen = ss.str();
    nazwaplikuocen += "-oceny.txt";
    std::fstream plikwej;
    plikwej.open(nazwaplikuocen, std::ios::in);
    if (!plikwej.is_open())
    {
        std::ofstream plikwyj;
        plikwyj.open(nazwaplikuocen, std::ios::out);
        if (!plikwyj.is_open())
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Błąd. Nie udało się poprawnie otworzyć pliku ocen. Wyłącz program i spróbuj ponownie");
            okienko->show();
        }
        plikwyj.close();
    }
    else
    {
        int lokID;
        double lokwartosc;
        int lokIDprzedm;
        std::string lokopis;
        while (!plikwej.eof())
        {
            plikwej >> lokID;
            if(plikwej.eof())
                break;      //zawsze wczytuje jakas wartosc nawet przy pustym dlatego break
            plikwej >> lokwartosc;
            plikwej >> lokIDprzedm;
            plikwej >> lokopis;
            if (lokopis == "<pusty>")
                lokopis = "";
            try {
                mapaocen->insert(std::pair<int, std::shared_ptr<ocena>>(lokID,
                                 std::shared_ptr<ocena>(new ocena(lokwartosc, mapaprzedmiotow->at(lokIDprzedm).get()))));
            }
            catch (std::exception)
            {
                okienko.reset(new QMessageBox);
                okienko->setText("Błąd. Nie udało się wczytać ocen. Wyłącz program i spróbuj ponownie.");
                okienko->show();
            }
        }
        plikwej.close();
    }
    if (mapaocen->size() > 0)
        numeratorocen = std::get<0>(*mapaocen->rbegin());
    else
        numeratorocen = 0;
}

void OknoGlowne::wyswietlanie()
{
    ui->listWidget->clear();
    for (int i=0; i<wektoralarmow->size(); i++)
    {
        ui->listWidget->addItem(QString::number(wektoralarmow->at(i).dajdate()));
    }
}
void OknoGlowne::wykonajkalendarz()
{

    time_t czaspocz = 0;
    tm* reprezentacja = localtime(&czaspocz);
    char bufor[20];
    setlocale( LC_ALL, "Polish" );
    for (int i = 0; i < miesiace.size(); i++)
    {
        strftime(bufor, sizeof(bufor), "%B", reprezentacja );
        bufor[0]-=32;
        //std::string buf = bufor;
        miesiace.at(i) = bufor;
        reprezentacja->tm_mon++;
    }
    czaspocz = time(NULL);
    reprezentacja = localtime(&czaspocz);
    aktmiesiac = reprezentacja->tm_mon;
    aktrok = reprezentacja->tm_year;
    //QTextCodec::setCodecForTr (QTextCodec::codecForName ("Windows-1250"));
    QString data;
    data = QString::fromStdString(miesiace.at(aktmiesiac))+" "+QString::number(aktrok + 1900);
    //const char* data2 = data.data();
    QString nowy(data);
    ui->label->setText(nowy);

}

OknoGlowne::~OknoGlowne()
{
    przel = false;
    delete ui;
}
void OknoGlowne::widok()
{
    time_t czas = time(NULL);
    tm* czas2 = localtime(&czas);
    czas2->tm_mday = 1;
    czas2->tm_mon = aktmiesiac;
    czas2->tm_year = aktrok;
    //czas2->tm_isdst = 0;
    mktime(czas2);
    for (int i = 0; i < 42; i++)
    {
        ui->widgety[i]->hide();
        ui->etykiety[i]->hide();
    }
    int dt = czas2->tm_wday;
    if(!dt)
        dt+=7;
    int koniec;
    if (czas2->tm_mon == 0 || czas2->tm_mon == 2 || czas2->tm_mon == 4 || czas2->tm_mon == 6 || czas2->tm_mon == 7 || czas2->tm_mon == 9 || czas2->tm_mon == 11)
    {
        koniec = 31 + dt -1;
    } else if (czas2->tm_mon == 3 || czas2->tm_mon == 5 || czas2->tm_mon == 8 || czas2->tm_mon == 10)
    {
        koniec = 30 + dt -1;
    } else if ((!((czas2->tm_year+1900) % 4) && ((czas2->tm_year+1900) % 100)) || !((czas2->tm_year+1900) % 400))
    {
        koniec = 29 + dt -1;
    } else
    {
        koniec = 28 + dt -1;
    }
    for (int i = dt - 1; i < koniec ; i++)
    {
        ui->widgety[i]->show();
        ui->etykiety[i]->show();
        ui->etykiety[i]->setText(QString::number(i-dt+2));
        ui->widgety[i]->clear();
    }
    std::vector<alarm>::iterator it;
    for (it = wektoralarmow->begin(); it != wektoralarmow->end(); it++)
    {
        time_t czlok = (*it).dajdate();
        tm * czlok2 = localtime(&czlok);
        if (czlok2->tm_year == aktrok && czlok2->tm_mon == aktmiesiac)
        {
            ui->widgety[dt - 1 + czlok2->tm_mday - 1]->addItem("alarm");
        }

    }
    std::map<int,std::shared_ptr<wydarzenie>>::iterator it2;
    for (it2 = mapawydarzen->begin(); it2 != mapawydarzen->end(); it2++)
    {
        std::shared_ptr<wydarzenie> lokwyd = std::get<1>(*it2);
        time_t czlok = lokwyd->dajdate();
        tm * czlok2 = localtime(&czlok);
        if (czlok2->tm_year == aktrok && czlok2->tm_mon == aktmiesiac)
        {
            std::string klasa = typeid(*lokwyd.get()).name();
            klasa.erase(0, 6);
            przedmiot* przed = lokwyd->dajprzedm();
            std::string przstr;
            if (przed)
                przstr = przed->dajnazwe();
            else
                przstr = "<brak>";
            ui->widgety[dt - 1 + czlok2->tm_mday - 1]->addItem(QString::fromStdString(klasa)+"|"+QString::fromStdString(przstr)+"|"+
                                                               QString::fromStdString(lokwyd->dajnazwe()));
        }

    }
    std::map<int,std::shared_ptr<zajecia>>::iterator it3;
    for (it3 = mapazajec->begin(); it3 != mapazajec->end(); it3++)
    {
        std::shared_ptr<zajecia> lokwyd = std::get<1>(*it3);
        std::vector<time_t> tabdat = lokwyd->dajdaty();
        for (int i = 0; i < tabdat.size(); i++)
        {
            tm * czlok2 = localtime(&tabdat[i]);
            if (czlok2->tm_year == aktrok && czlok2->tm_mon == aktmiesiac)
            {
                std::string klasa = typeid(*lokwyd.get()).name();
                klasa.erase(0, 6);
                std::string prz = lokwyd->dajprzedm()->dajnazwe();

                ui->widgety[dt - 1 + czlok2->tm_mday - 1]->addItem(QString::fromStdString(klasa)+"|"+QString::fromStdString(prz));
            }

        }
    }
}

void OknoGlowne::on_wczesniej_clicked()
{
    if(!aktmiesiac)
    {
        aktmiesiac = 11;
        aktrok--;
    }
    else
        aktmiesiac--;
    ui->label->setText(QString::fromStdString(miesiace.at(aktmiesiac))+" "+QString::number(aktrok + 1900));
    widok();
}

void OknoGlowne::on_pozniej_clicked()
{
    if(aktmiesiac == 11)
    {
        aktmiesiac = 0;
        aktrok++;
    }
    else
        aktmiesiac++;
    ui->label->setText(QString::fromStdString(miesiace.at(aktmiesiac))+" "+QString::number(aktrok + 1900));
    widok();
    //wyswietlanie();
}

void OknoGlowne::on_actionAlarm_triggered()
{
    nowyalarm.reset(new oknoalarmu(wektoralarmow, nrprofilu, nazwaplikualarmow));
    nowyalarm->show();
}

void OknoGlowne::on_actionOcena_triggered()
{
    nowaocena.reset(new oknooceny(mapaocen, mapaprzedmiotow, &numeratorocen, nazwaplikuocen));
    nowaocena->show();
}

void OknoGlowne::on_actionPrzedmiot_triggered()
{
    nowyprzedmiot.reset(new oknoprzedmiotu(mapaprzedmiotow, &numeratorprzedm));
    nowyprzedmiot->show();
}

void OknoGlowne::on_actionZako_cz_triggered()
{
    close();
}

void OknoGlowne::on_actionZaj_cia_triggered()
{
    nowezajecie.reset(new oknozajec(mapazajec, mapaprzedmiotow, &numeratorzaj, nazwaplikuzaj));
    nowezajecie->show();
}

void OknoGlowne::on_actionWydarzenie_triggered()
{
    nowewydarzenie.reset(new oknowydarzenia(mapawydarzen, mapaprzedmiotow, nazwaplikuwydarzen, &numeratorwyd));
    nowewydarzenie->show();
}

void OknoGlowne::on_pushButton_clicked()
{
    widok(); //odswiezanie widoku co sekunde
    while(!listazdarzen->empty())   //mozna ifem i w kazde sekundzie zdejmowac jeden
    {
        std::string tytul = std::get<0>(listazdarzen->front());
        tytul.erase(0,6);
        std::string nazwa = std::get<1>(listazdarzen->front());
        listazdarzen->pop_front();
        if (tytul == "alarm")
        {   //obsluga alarmu - w nazwie wpisane wartosci
            int rodzaj = nazwa[0] - 48;
            nazwa.erase(0, 2);
            int glos = std::stoi(nazwa);
            Beep(99*glos + 38, (2*rodzaj + 1)*1000);
            nazwa = "";
        }
        okienko.reset(new QMessageBox);
        okienko->setText(QString::fromStdString(tytul));
        okienko->setInformativeText(QString::fromStdString(nazwa));
        okienko->show();
    }
}

void OknoGlowne::on_actionO_programie_triggered()
{
    noweusuwanie.reset(new oknousuwania(wektoralarmow, mapaocen, mapaprzedmiotow, mapawydarzen, mapazajec,
                                        nazwaplikualarmow, nazwaplikuocen, "przedmioty.txt", nazwaplikuwydarzen, nazwaplikuzaj));
    noweusuwanie->show();
}

void OknoGlowne::on_actionOceny_triggered()
{
    std::string wynik ="";
    std::map<int,std::shared_ptr<ocena>>::iterator ito;
    for (ito = mapaocen->begin(); ito != mapaocen->end(); ito++)
    {
        std::shared_ptr<ocena> lok = std::get<1>(*ito);
        wynik += lok->dajprzedm()->dajnazwe();
        wynik += ":";
        wynik += std::to_string(lok->dajwartosc());
        wynik += "\n";
    }
    okienko.reset(new QMessageBox);
    okienko->setText(QString::fromStdString(wynik));
    okienko->setMinimumSize(QSize(400,300));
    okienko->show();
}

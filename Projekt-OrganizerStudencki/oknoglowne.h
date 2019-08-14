#ifndef OKNOGLOWNE_H
#define OKNOGLOWNE_H
#include <QApplication>
#include <QMainWindow>
#include <array>
#include "oknoalarmu.h"
#include "oknooceny.h"
#include "oknoprzedmiotu.h"
#include "oknowydarzenia.h"
#include "oknozajec.h"
#include "oknousuwania.h"
#include "alarm.h"
#include "ocena.h"
#include "profil.h"
#include "przedmiot.h"
#include "wydarzenie.h"
#include "zajecia.h"
#include <memory>
namespace Ui {
class OknoGlowne;
}

class OknoGlowne : public QMainWindow
{
    Q_OBJECT

public:
    explicit OknoGlowne(QWidget *parent = 0);
    explicit OknoGlowne(const std::shared_ptr<std::vector<alarm>> &,    //otrzymuje wskaźniki do kontenerów i nr usera
                        const std::shared_ptr<std::map<int,std::shared_ptr<wydarzenie>>>& wydarzenia,
                        const std::shared_ptr<std::map<int,std::shared_ptr<zajecia>>> & zajecia, int _nrprofilu,
                        const std::shared_ptr<std::list<std::pair<std::string, std::string>>>& _listazdarzen);
    ~OknoGlowne();


private slots:
    void on_wczesniej_clicked();

    void on_pozniej_clicked();

    void on_actionAlarm_triggered();

    void on_actionOcena_triggered();

    void on_actionPrzedmiot_triggered();    //metody obsługujące ui

    void on_actionZako_cz_triggered();

    void on_actionZaj_cia_triggered();

    void on_actionWydarzenie_triggered();

    void on_pushButton_clicked();

    void on_actionO_programie_triggered();

    void on_actionOceny_triggered();

private:
    Ui::OknoGlowne *ui;
    std::array<std::string, 12> miesiace;
    bool przel; //przelacznik do watku
    int aktmiesiac;
    int aktrok;
    int nrprofilu;
    int numeratorprzedm;    //dane do nadawnia id
    int numeratorwyd;
    int numeratorzaj;
    int numeratorocen;
    std::unique_ptr<oknoalarmu> nowyalarm;  //wskaźniki na okienka - singletony
    std::unique_ptr<oknooceny> nowaocena;
    std::unique_ptr<oknoprzedmiotu> nowyprzedmiot;
    std::unique_ptr<oknowydarzenia> nowewydarzenie;
    std::unique_ptr<oknozajec> nowezajecie;
    std::unique_ptr<oknousuwania> noweusuwanie;
    std::unique_ptr<QMessageBox> okienko;
    std::shared_ptr<std::vector<alarm>> wektoralarmow;  //kontenery przechowujące odpowiednie obiekty
    std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> mapaprzedmiotow;
    std::shared_ptr<std::map<int,std::shared_ptr<zajecia>>> mapazajec;
    std::shared_ptr<std::map<int,std::shared_ptr<wydarzenie>>> mapawydarzen;
    std::shared_ptr<std::map<int,std::shared_ptr<ocena>>> mapaocen;
    std::shared_ptr<std::list<std::pair<std::string, std::string>>> listazdarzen;
    std::string nazwaplikualarmow;
    std::string nazwaplikuwydarzen; //nazwy plików
    std::string nazwaplikuzaj;
    std::string nazwaplikuocen;
    void wykonajkalendarz();
    void widok();
    void wyswietlanie();
    void sprawdzanie(bool &przel);
    void wczytaniealarmow();
    void wczytanieprzedmiotow();
    void wczytaniewydarzen();
    void wczytaniezajec();
    void wczytanieocen();
};

#endif // OKNOGLOWNE_H

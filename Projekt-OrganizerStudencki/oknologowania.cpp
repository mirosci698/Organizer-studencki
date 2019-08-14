#include "oknologowania.h"
#include "ui_oknologowania.h"
#include <iostream>
#include <fstream>
#define PLIKWEJ "profile.txt"
OknoLogowania::OknoLogowania(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OknoLogowania)
{
    ui->setupUi(this);
}

OknoLogowania::OknoLogowania(int* _nrprofilu): QMainWindow(NULL), ui(new Ui::OknoLogowania)
{
    ui->setupUi(this);
    profile.reset(new std::vector<profil>);
    nrprofilu = _nrprofilu;//adres gdzie dam nmer profilu z ktorego korzystamy
    std::fstream plikwej;
    plikwej.open(PLIKWEJ, std::ios::in);    //odczyt pliku
    if (!plikwej.is_open())
    {
        std::ofstream plikwyj;
        plikwyj.open(PLIKWEJ, std::ios::out);   //jezeli nie oworzyl sie to robimy nowy o tej nazwie
        if (!plikwyj.is_open())
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Błąd. Nie udało się poprawnie otworzyć pliku profili. Wyłącz program i spróbuj ponownie");
            okienko->show();
        }
        plikwyj.close();
    }
    else
    {
        std::string lokhaslo;
        std::string loklogin;
        int lokID;
        while (!plikwej.eof())
        {
            plikwej >> lokID;   //wczyt olejnych wartosci z pliku
            if(plikwej.eof())
                break;      //zawsze wczytuje jakas wartosc nawet przy pustym dlatego break
            plikwej >> loklogin;
            plikwej >> lokhaslo;
            try {
                profile->push_back(profil(loklogin, lokhaslo));
            }
            catch (std::exception)
            {
                okienko.reset(new QMessageBox);
                okienko->setText("Błąd. Nie udało się wczytać profili. Wyłącz program i spróbuj ponownie.");
                okienko->show();
            }
        }
        if (profile->size() > 0)
            profil::wpiszprzyd(profile->back().dajID());    //wczytanie ostatniego jako ID do zwiekszenia przy odczycie
        plikwej.close();
    }
}

OknoLogowania::~OknoLogowania()
{
    delete ui;  //stworzone przez srodowisko
}

void OknoLogowania::on_przycisklogowania_clicked()
{
    std::string login = ui->poleloginu->text().toStdString();
    std::string haslo = ui->polehasla->text().toStdString();    //zczytywanie z pol
    ui->poleloginu->clear();
    ui->polehasla->clear();
    //bool blad = false;
    for (int i = 0; i <haslo.length(); i++)
        if ((haslo[i] < 65 || haslo[i] > 90) && (haslo[i] < 97 || haslo[i] > 122))
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Użyj w haśle tylko dużych i małych liter.");
            okienko->show();
            //blad = true;
            return;
        }
    for (int i = 0; i <login.length(); i++)         //zabezpieczenia na odpowiednie wartosci
        if ((login[i] < 65 || login[i] > 90) && (login[i] < 97 || login[i] > 122))
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Użyj w loginie tylko dużych i małych liter.");
            okienko->show();
            //blad = true;
            return;
        }
    haslo = profil::zaszyfruj(haslo);
    bool znaleziono = false;
    std::vector<profil>::iterator it;   //szukanie we wczytanych z pliku profilach
    for (it = profile->begin(); it != profile->end(); it++)
    {
        if ((*it).sprawdzlogin(login))
            if ((*it).sprawdzhaslo(haslo))
            {
                znaleziono = true;
                *nrprofilu = (*it).dajID(); //zwrot do glownego sterowania numeru profilu
                break;
            }
    }
    if (!znaleziono)
    {
        okienko.reset(new QMessageBox);
        okienko->setText("Blad logowania.");
        okienko->show();
    }
    else
    {
            this->close();
    }
}

void OknoLogowania::on_przycisknowegokonta_clicked()
{
    std::string login = ui->poleloginu->text().toStdString();
    std::string haslo = ui->polehasla->text().toStdString();
    ui->poleloginu->clear();
    ui->polehasla->clear(); //zczyt z pól i ich wyczyszczenie
    for (int i = 0; i <haslo.length(); i++)
        if ((haslo[i] < 65 || haslo[i] > 90) && (haslo[i] < 97 || haslo[i] > 122))
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Użyj w haśle tylko dużych i małych liter.");
            okienko->show();
            return;     //zabezpieczenia na odpowiednie znaki w loginie i hasle
        }
    for (int i = 0; i <login.length(); i++)
        if ((login[i] < 65 || login[i] > 90) && (login[i] < 97 || login[i] > 122))
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Użyj w loginie tylko dużych i małych liter.");
            okienko->show();
            return;
        }
    std::vector<profil>::iterator it;
    bool powtorka = false;
    for (it = profile->begin(); it != profile->end(); it++)
    {
        if ((*it).sprawdzlogin(login)) //sprawdzanie czy jest juz w bazie
            {
                okienko.reset(new QMessageBox);
                okienko->setText("Jest taki w bazie");
                okienko->show();
                powtorka = true;
                break;
            }
    }
    if (!powtorka) //jezeli nie bylo w bazie
    {
        try {   // przy konstruktorze profilu może pójść wyjątek
             profile->push_back(profil(login,profil::zaszyfruj(haslo)));
             std::ofstream plikwyj;
             plikwyj.open(PLIKWEJ, std::ios::app); //zapisywanie na koniec pliku profili
             bool blad2 = false;
             if (!plikwyj.is_open())
             {
                 okienko.reset(new QMessageBox);
                 okienko->setText("Błąd zapisu do pliku profili.");
                 okienko->show();
                 blad2 = true;
             }
             else
             {
                 plikwyj << profile->back().dajID() << " " <<profile->back().dajlogin() <<" " << profile->back().dajhaslo() << std::endl;
                 plikwyj.close();   //wpis do pliku i zamkniecie
             }
             if(!blad2)
             {
                 *nrprofilu = profile->back().dajID(); //nadanie nr profilu
                 this->close();
             }
        }
        catch (std::exception)
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Błąd.");
            okienko->show();
        }
    }
}

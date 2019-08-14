#include "oknoalarmu.h"
#include "ui_oknoalarmu.h"
#include <iostream>
#include <ctime>
#include <QMediaPlayer>
#include <sstream>
#include <fstream>
oknoalarmu::oknoalarmu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oknoalarmu)
{
    ui->setupUi(this);
}

oknoalarmu::oknoalarmu(std::shared_ptr<std::vector<alarm>> _alarmy, int nrusera, std::string _nazwapliku):
    QDialog(NULL),
    ui(new Ui::oknoalarmu)
{
    ui->setupUi(this);
    alarmy = _alarmy;
    ui->comboBox->addItem("1 sekunda");
    ui->comboBox->addItem("3 sekundy");
    ui->comboBox->addItem("5 sekund");
    nazwapliku = _nazwapliku;

}

oknoalarmu::~oknoalarmu()
{
    delete ui;
}

void oknoalarmu::on_przyciski_accepted()
{
    std::string sciezka =""; // ui->sciezka->text().toStdString();
    uint moment = ui->dataigodzina->dateTime().toTime_t();
    int glosnosc = ui->glosnosc->value();
    int typ = ui->comboBox->currentIndex();
    time_t moment2 = moment;
    std::vector<alarm>::iterator it;
    bool powtorka = false;
    for (it = alarmy->begin(); it != alarmy->end(); it++)
    {
        if ((*it).sprawdzmoment(moment2))
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Błąd. Jest już alarm o tej godzinie.");
            okienko->show();
            powtorka = true;
        }
    }
    if (!powtorka)
    {
        try {
         alarmy->push_back(alarm(moment2, typ, glosnosc));
         std::ofstream plikwyj;
         plikwyj.open(nazwapliku, std::ios::app);
         if (!plikwyj.is_open())
         {
             okienko.reset(new QMessageBox);
             okienko->setText("Błąd. Nie udało się wczytać alarmów. Wyłącz program i spróbuj ponownie.");
             okienko->show();
         }
         else
         {
            plikwyj << alarmy->back().dajdate() << " " << alarmy->back().dajdzwiek() << " "  << alarmy->back().dajglosnosc() << std::endl;
            plikwyj.close();
         }
         this->close();
        }

        catch(std::exception)
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Błąd. Spróbuj jeszcze raz.");
            okienko->show();
        }
    }
}

void oknoalarmu::on_przyciski_rejected()
{
    close();
}


void oknoalarmu::on_glosnosc_sliderReleased()
{
    std::cout << ui->glosnosc->value() << std::endl;
}

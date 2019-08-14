#include "oknoprzedmiotu.h"
#include "ui_oknoprzedmiotu.h"
#include <QMessageBox>
#define PLIKWEJ "przedmioty.txt"
#include <fstream>
#include <utility>
oknoprzedmiotu::oknoprzedmiotu(QWidget *parent): QDialog(parent), ui(new Ui::oknoprzedmiotu)
{
    ui->setupUi(this);
}
oknoprzedmiotu::oknoprzedmiotu(std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> _mapaprzedmiotow,
                               int* _numeratorprzedm): QDialog(NULL), ui(new Ui::oknoprzedmiotu)
{
    ui->setupUi(this);
    //przedmioty = _przedmioty;
    //mapaprzedmiotow.reset(new std::map<int,std::shared_ptr<przedmiot>>);
    mapaprzedmiotow = _mapaprzedmiotow;
    if (mapaprzedmiotow.get() == NULL)
        mapaprzedmiotow.reset(new std::map<int,std::shared_ptr<przedmiot>>);
    numerator = _numeratorprzedm;

}
oknoprzedmiotu::~oknoprzedmiotu()
{
    delete ui;
}
void oknoprzedmiotu::on_buttonBox_accepted()
{
    std::string nazwa = ui->lineEdit->text().toStdString();
    std::string imie = ui->lineEdit_2->text().toStdString();
    std::string nazwisko = ui->lineEdit_3->text().toStdString();
    int punkty = ui->spinBox->value();
    std::string opis = ui->plainTextEdit->toPlainText().toStdString();
    if (opis.length() == 0)
        opis = "<pusty>";
    try {
        mapaprzedmiotow->insert(std::pair<int, std::shared_ptr<przedmiot>>(++(*numerator), std::shared_ptr<przedmiot>(new przedmiot(nazwa, nazwisko, imie, punkty, opis))));
        std::ofstream plikwej;
        plikwej.open(PLIKWEJ, std::ios::app);
        bool blad = false;
        if (!plikwej.is_open())
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Błąd zapisu do pliku przedmiotów.");
            okienko->show();
            blad = true;
        }
        else
        {
            plikwej << std::get<0>((*mapaprzedmiotow->rbegin())) << " ";
            std::shared_ptr<przedmiot> lokalny = std::get<1>((*mapaprzedmiotow->rbegin()));
            plikwej << lokalny->dajnazwe() << " " << lokalny->dajprowadzacego() << " " << lokalny->dajECTS() << " " << lokalny->dajopis() << std::endl;
            plikwej.close();
        }
        if (!blad)
            this->close();
    }
    catch(std::exception)
    {
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->spinBox->setValue(0);
        ui->plainTextEdit->clear();
        okienko.reset(new QMessageBox);
        okienko->setText("Błąd. Spróbuj jeszcze raz.");
        okienko->show();
    }
}
void oknoprzedmiotu::on_buttonBox_rejected()
{
    this->close();
}

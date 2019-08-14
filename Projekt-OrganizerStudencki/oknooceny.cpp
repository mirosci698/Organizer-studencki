#include "oknooceny.h"
#include "ui_oknooceny.h"
#include <iostream>
#include <fstream>
#include <sstream>
oknooceny::oknooceny(QWidget *parent): QDialog(parent), ui(new Ui::oknooceny)
{
    ui->setupUi(this);
}
oknooceny::oknooceny(std::shared_ptr<std::map<int,std::shared_ptr<ocena>>> _mapaocen,
                     std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> _mapaprzedmiotow,
                     int* _numerator, std::string _nazwapliku):
    QDialog(NULL),
    ui(new Ui::oknooceny)
{
    ui->setupUi(this);
    //oceny = _oceny;
    //przedmioty = _przedmioty;
    numerator = _numerator;
    nazwapliku = _nazwapliku;
    mapaocen = _mapaocen;
    mapaprzedmiotow = _mapaprzedmiotow;
    ui->comboBox->addItem("<wybierz przedmiot>");
    std::map<int,std::shared_ptr<przedmiot>>::iterator it;
    for (it = mapaprzedmiotow->begin(); it !=mapaprzedmiotow->end(); it++)
    {
        int numer = std::get<0>(*it);
        std::shared_ptr<przedmiot> wskaz = std::get<1>(*it);
        ui->comboBox->addItem(QString::number(numer)+":"+QString::fromStdString(wskaz->dajnazwe()));
    }
}
oknooceny::~oknooceny()
{
    delete ui;
}
void oknooceny::on_buttonBox_accepted()
{
    double wartosc = ui->lineEdit->text().toDouble();
    std::string opis = ui->plainTextEdit->toPlainText().toStdString();
    std::string str = ui->comboBox->currentText().toStdString();
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ':')
        {
            str.erase(i,str.length() - i);
        }
    }
    int indeks;
    if(ui->comboBox->currentIndex() != 0)
        indeks = std::stoi(str);
    else
        indeks = -1;
    try {
        mapaocen->insert(std::pair<int, std::shared_ptr<ocena>>(++(*numerator),
                         std::shared_ptr<ocena>(new ocena(wartosc, mapaprzedmiotow->at(indeks).get(), opis))));
        std::ofstream plikwej;
        plikwej.open(nazwapliku, std::ios::app);
        bool blad = false;
        if (!plikwej.is_open())
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Błąd zapisu do pliku ocen.");
            okienko->show();
            blad = true;
        }
        else
        {
            plikwej << std::get<0>((*mapaocen->rbegin())) << " ";
            std::shared_ptr<ocena> lokalny = std::get<1>((*mapaocen->rbegin()));
            plikwej << lokalny->dajwartosc() << " " << indeks << " ";
            if (lokalny->dajopis() == "")
                plikwej<< "<pusty>" << std::endl;
            else
                plikwej<< lokalny->dajopis() << std::endl;
            plikwej.close();
        }
        this->close();
    }
    catch (std::exception)
    {
        ui->lineEdit->clear();
        ui->comboBox->setCurrentIndex(0);
        ui->plainTextEdit->clear();
        okienko.reset(new QMessageBox);
        okienko->setText("Błąd. Spróbuj jeszcze raz.");
        okienko->show();
    }
}
void oknooceny::on_buttonBox_rejected()
{
    this->close();
}
void oknooceny::on_comboBox_currentIndexChanged(int index)
{
    std::cout <<"obecny indeks "<< index << std::endl;
}

void oknooceny::on_checkBox_toggled(bool checked)
{

}

#include "oknowydarzenia.h"
#include "ui_oknowydarzenia.h"
#include <fstream>
oknowydarzenia::oknowydarzenia(QWidget *parent): QDialog(parent), ui(new Ui::oknowydarzenia)
{
    ui->setupUi(this);
}
oknowydarzenia::oknowydarzenia(std::shared_ptr<std::map<int,std::shared_ptr<wydarzenie>>> _mapawydarzen,
                               std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> _mapaprzedmiotow,
                               std::string _nazwapliku, int* _numerator):
    QDialog(NULL),
    ui(new Ui::oknowydarzenia)
{
    ui->setupUi(this);
    //wydarzenia = _wydarzenia;
    //przedmioty = _przedmioty;
    numerator = _numerator;
    mapaprzedmiotow = _mapaprzedmiotow;
    mapawydarzen= _mapawydarzen;
    nazwapliku = _nazwapliku;
    ui->comboBox->addItem("<wybierz przedmiot>");
    std::map<int,std::shared_ptr<przedmiot>>::iterator it;
    for (it = mapaprzedmiotow->begin(); it !=mapaprzedmiotow->end(); it++)
    {
        int numer = std::get<0>(*it);
        std::shared_ptr<przedmiot> wskaz = std::get<1>(*it);
        ui->comboBox->addItem(QString::number(numer)+":"+QString::fromStdString(wskaz->dajnazwe()));
    }
}
oknowydarzenia::~oknowydarzenia()
{
    delete ui;
}
void oknowydarzenia::on_buttonBox_rejected()
{
    this->close();
}
void oknowydarzenia::on_buttonBox_accepted()
{
    std::string nazwa = ui->lineEdit->text().toStdString();
    std::string opis = ui->plainTextEdit->toPlainText().toStdString();
    uint moment = ui->dateTimeEdit->dateTime().toTime_t();
    time_t moment2 = moment;
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
        if (ui->radioButton->isChecked())
        {
            mapawydarzen->insert(std::pair<int, std::shared_ptr<wydarzenie>>(++(*numerator),
            std::shared_ptr<wydarzenie>(new kartkowka(moment2, nazwa, opis,
            mapaprzedmiotow->at(indeks).get()))));
        } else if (ui->radioButton_2->isChecked())
        {
            mapawydarzen->insert(std::pair<int, std::shared_ptr<wydarzenie>>(++(*numerator),
            std::shared_ptr<wydarzenie>(new kolokwium(moment2, nazwa, opis,
            mapaprzedmiotow->at(indeks).get()))));
        } else if (ui->radioButton_3->isChecked())
        {
            mapawydarzen->insert(std::pair<int, std::shared_ptr<wydarzenie>>(++(*numerator),
            std::shared_ptr<wydarzenie>(new egzamin(moment2, nazwa, opis,
            mapaprzedmiotow->at(indeks).get()))));
        } else if (ui->radioButton_4->isChecked())
        {
            mapawydarzen->insert(std::pair<int, std::shared_ptr<wydarzenie>>(++(*numerator),
            std::shared_ptr<wydarzenie>(new inne(moment2, nazwa, opis))));
        }
        else
        {
            throw std::exception();
        }
        std::ofstream plikwej;
        plikwej.open(nazwapliku, std::ios::app);
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
            plikwej << std::get<0>((*mapawydarzen->rbegin())) << " ";
            std::shared_ptr<wydarzenie> lokalny = std::get<1>((*mapawydarzen->rbegin()));
            plikwej << lokalny->dajdate() << " " << lokalny->dajnazwe() << " ";
            std::string klasa = typeid(*lokalny.get()).name();
            klasa.erase(0, 6);
            plikwej << klasa << " ";
            if (typeid(*lokalny.get()).name()!= "class inne")
                plikwej << indeks << " ";
            else
                plikwej << indeks << " ";
            if (lokalny->dajopis() == "")
                plikwej<< "<pusty>" << std::endl;
            else
                plikwej<< lokalny->dajopis() << std::endl;
            plikwej.close();
        }
        this->close();
    }
    catch(std::exception)
    {
        ui->lineEdit->clear();
        ui->plainTextEdit->clear();
        ui->comboBox->setCurrentIndex(0);
        okienko.reset(new QMessageBox);
        okienko->setText("Błąd. Spróbuj jeszcze raz.");
        okienko->show();
    }
}

void oknowydarzenia::on_radioButton_4_toggled(bool checked)
{
    if (checked)
        ui->comboBox->setDisabled(true);
    else
        ui->comboBox->setEnabled(true);
}

#include "oknozajec.h"
#include "ui_oknozajec.h"
#include <iterator>
#include <utility>
#include <fstream>
#include <sstream>
oknozajec::oknozajec(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oknozajec)
{
    ui->setupUi(this);
}
oknozajec::oknozajec(std::shared_ptr<std::map<int,std::shared_ptr<zajecia>>> _mapazajec,
                     std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> _mapaprzedmiotow,
                     int* _numerator, std::string _nazwapliku):
    QDialog(NULL),
    ui(new Ui::oknozajec)
{
    ui->setupUi(this);
    //kontenerzajecia = _zajecia;
    //kontenerprzedmioty = _przedmioty;
    mapaprzedmiotow = _mapaprzedmiotow;
    mapazajec = _mapazajec;
    numerator = _numerator;
    nazwapliku = _nazwapliku;
    ui->comboBox->addItem("<wybierz przedmiot>");
    std::map<int,std::shared_ptr<przedmiot>>::iterator it;
    for (it = mapaprzedmiotow->begin(); it != mapaprzedmiotow->end(); it++)
    {
        int a = std::get<0>(*it);
        std::shared_ptr<przedmiot> b =  std::get<1>(*it);
        ui->comboBox->addItem(QString::number(a) + "." + QString::fromStdString(b->dajnazwe()));
    }
    //for (int i = 0; i < kontenerprzedmioty->size(); i++)
    //{
    //    ui->comboBox->addItem(QString::fromStdString(kontenerprzedmioty->at(i)->dajnazwe()));
    //}
}
oknozajec::~oknozajec()
{
    delete ui;
}
void oknozajec::on_buttonBox_accepted()
{
    std::string str = ui->comboBox->currentText().toStdString();
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '.')
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
            mapazajec->insert(std::pair<int,std::shared_ptr<zajecia>>(++(*numerator), std::shared_ptr<zajecia>(new wyklad(mapaprzedmiotow->at(indeks).get()))));
            mapazajec->at(*numerator)->wpiszdaty(daty);
        } else if (ui->radioButton_2->isChecked())
        {
            mapazajec->insert(std::pair<int,std::shared_ptr<zajecia>>(++(*numerator),
                              std::shared_ptr<zajecia>(new cwiczenia(mapaprzedmiotow->at(indeks).get()))));
            mapazajec->at(*numerator)->wpiszdaty(daty);
        } else if (ui->radioButton_3->isChecked())
        {
            mapazajec->insert(std::pair<int,std::shared_ptr<zajecia>>(++(*numerator),
                              std::shared_ptr<zajecia>(new laboratorium(mapaprzedmiotow->at(indeks).get()))));
            mapazajec->at(*numerator)->wpiszdaty(daty);
        } else if (ui->radioButton_4->isChecked())
        {
            mapazajec->insert(std::pair<int,std::shared_ptr<zajecia>>(++(*numerator),
                              std::shared_ptr<zajecia>(new projekt(mapaprzedmiotow->at(indeks).get()))));
            mapazajec->at(*numerator)->wpiszdaty(daty);
        } else if (ui->radioButton_5->isChecked())
        {
            mapazajec->insert(std::pair<int,std::shared_ptr<zajecia>>(++(*numerator),
                              std::shared_ptr<zajecia>(new seminarium(mapaprzedmiotow->at(indeks).get()))));
            mapazajec->at(*numerator)->wpiszdaty(daty);
        } else if (ui->radioButton_6->isChecked())
        {
            mapazajec->insert(std::pair<int,std::shared_ptr<zajecia>>(++(*numerator),
                              std::shared_ptr<zajecia>(new praktyka(mapaprzedmiotow->at(indeks).get()))));
            mapazajec->at(*numerator)->wpiszdaty(daty);
        } else
        {
            throw std::exception();
        }
        for(int i = 0; i < daty.size(); i++)
        {
            daty.pop_back();
        }
        std::ofstream plikwej;
        plikwej.open(nazwapliku, std::ios::app);
        bool blad = false;
        if (!plikwej.is_open())
        {
            okienko.reset(new QMessageBox);
            okienko->setText("Błąd zapisu do pliku zajęć.");
            okienko->show();
            blad = true;
        }
        else
        {
            plikwej << std::get<0>((*mapazajec->rbegin())) << " ";
            std::shared_ptr<zajecia> lokalny = std::get<1>((*mapazajec->rbegin()));
            std::string klasa = typeid(*lokalny.get()).name();
            klasa.erase(0, 6);
            plikwej << klasa << " ";
            plikwej << indeks << " ";
            plikwej << lokalny->dajdaty().size();
            for (int i = 0; i < lokalny->dajdaty().size(); i++)
            {
                plikwej << " " << lokalny->dajdaty().at(i);
            }
            plikwej << std::endl;

            plikwej.close();
        }
        this->close();
    }
    catch (std::exception)
    {
        okienko.reset(new QMessageBox);
        okienko->setText("Błąd. Spróbuj jeszcze raz.");
        okienko->show();
    }
}
void oknozajec::on_buttonBox_rejected()
{
    this->close();
}
void oknozajec::on_pushButton_clicked()
{
    daty.push_back(ui->dateTimeEdit->dateTime().toTime_t());
    QString data = ui->dateTimeEdit->dateTime().toString();
    ui->listWidget->addItem(data);

}

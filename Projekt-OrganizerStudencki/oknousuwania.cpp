#include "oknousuwania.h"
#include "ui_oknousuwania.h"
#include <fstream>
oknousuwania::oknousuwania(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oknousuwania)
{
    ui->setupUi(this);
}
oknousuwania::oknousuwania(const std::shared_ptr<std::vector<alarm>> & alarmy,
                           const std::shared_ptr<std::map<int,std::shared_ptr<ocena>>> & oceny,
                           const std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> & przedmioty,
                           const std::shared_ptr<std::map<int,std::shared_ptr<wydarzenie>>>& wydarzenia,
                           const std::shared_ptr<std::map<int,std::shared_ptr<zajecia>>> & konzajecia,
                           std::string na, std::string no, std::string np, std::string nw, std::string nz) :
    QDialog(NULL),
    ui(new Ui::oknousuwania)
{
    ui->setupUi(this);
    nazwaplikualarmow = na;
    nazwaplikuocen = no;
    nazwaplikuprzed = np;
    nazwaplikuwydarzen = nw;
    nazwaplikuzaj = nz;
    wektoralarmow = alarmy;
    mapaprzedmiotow = przedmioty;
    mapaocen = oceny;
    mapawydarzen = wydarzenia;
    mapazajec = konzajecia;
    std::vector<alarm>::iterator ita;
    for (ita = wektoralarmow->begin(); ita != wektoralarmow->end(); ita++)
    {
        time_t a = (*ita).dajdate();
        ui->comboBox->addItem(QString::number((*ita).dajdate())+"|"+QString(ctime(&a)));
    }
    std::map<int,std::shared_ptr<ocena>>::iterator ito;
    for (ito = mapaocen->begin(); ito != mapaocen->end(); ito++)
    {
        int numer = std::get<0>(*ito);
        std::shared_ptr<ocena> lok = std::get<1>(*ito);
        ui->comboBox_2->addItem(QString::number(numer)+":"+QString::number(lok->dajwartosc())+"-"+
                                QString::fromStdString(lok->dajprzedm()->dajnazwe()));
    }
    std::map<int,std::shared_ptr<przedmiot>>::iterator itp;
    for (itp = mapaprzedmiotow->begin(); itp != mapaprzedmiotow->end(); itp++)
    {
        int numer = std::get<0>(*itp);
        std::shared_ptr<przedmiot> lok = std::get<1>(*itp);
        ui->comboBox_3->addItem(QString::number(numer)+":"+
                                QString::fromStdString(lok->dajnazwe()));
    }

    std::map<int,std::shared_ptr<wydarzenie>>::iterator itw;
    for (itw = mapawydarzen->begin(); itw != mapawydarzen->end(); itw++)
    {
        int numer = std::get<0>(*itw);
        std::shared_ptr<wydarzenie> lok = std::get<1>(*itw);
        ui->comboBox_4->addItem(QString::number(numer)+":"+
                                QString::fromStdString(lok->dajnazwe()));
    }
    std::map<int,std::shared_ptr<zajecia>>::iterator itz;
    for (itz = mapazajec->begin(); itz != mapazajec->end(); itz++)
    {
        int numer = std::get<0>(*itz);
        std::shared_ptr<zajecia> lok = std::get<1>(*itz);
        ui->comboBox_5->addItem(QString::number(numer)+":"+
                                QString::fromStdString(lok->dajprzedm()->dajnazwe())+":"+
                                QString::fromStdString(typeid(*(lok.get())).name()));
    }
}
oknousuwania::~oknousuwania()
{
    delete ui;
}

void oknousuwania::on_radioButton_toggled(bool checked)
{
    if (checked)
        ui->comboBox->setEnabled(true);
    else
        ui->comboBox->setDisabled(true);
}

void oknousuwania::on_radioButton_2_toggled(bool checked)
{
    if (checked)
        ui->comboBox_2->setEnabled(true);
    else
        ui->comboBox_2->setDisabled(true);
}

void oknousuwania::on_radioButton_3_toggled(bool checked)
{
    if (checked)
        ui->comboBox_3->setEnabled(true);
    else
        ui->comboBox_3->setDisabled(true);
}

void oknousuwania::on_radioButton_4_toggled(bool checked)
{
    if (checked)
        ui->comboBox_4->setEnabled(true);
    else
        ui->comboBox_4->setDisabled(true);
}

void oknousuwania::on_radioButton_5_toggled(bool checked)
{
    if (checked)
        ui->comboBox_5->setEnabled(true);
    else
        ui->comboBox_5->setDisabled(true);
}

void oknousuwania::on_pushButton_clicked()
{
    if (ui->radioButton->isChecked())
    {
        std::string str = ui->comboBox->currentText().toStdString();
        for(int i = 0; i < str.length(); i++)
        {
            if (str[i] == '|')
                str.erase(i, str.length()-i);
        }
        time_t ind = std::stoi(str);
        std::vector<alarm> pom;
        for (int i = wektoralarmow->size() - 1; i >= 0; i--)
        {
            if (wektoralarmow->at(i).dajdate() != ind)
            {
                pom.push_back(wektoralarmow->at(i));
                wektoralarmow->pop_back();
            }
            else
            {
                wektoralarmow->pop_back();
                break;
            }
        }
        while (!pom.empty())
        {
            wektoralarmow->push_back(pom.back());
            pom.pop_back();
        }
        std::ofstream plik;
        plik.open(nazwaplikualarmow, std::ios::trunc);
        if(plik.is_open())
        {
            std::vector<alarm>::iterator ita;
            for (ita = wektoralarmow->begin(); ita != wektoralarmow->end(); ita++)
            {
                plik << (*ita).dajdate() << " " << (*ita).dajdzwiek() << " " << (*ita).dajglosnosc() << std::endl;

            }
            plik.close();
        }
        this->close();
    } else if (ui->radioButton_2->isChecked())
    {
        std::string str = ui->comboBox_2->currentText().toStdString();
        for(int i = 0; i < str.length(); i++)
        {
            if (str[i] == ':')
                str.erase(i, str.length()-i);
        }
        int ind = std::stoi(str);
        mapaocen->erase(ind);
        std::ofstream plik;
        plik.open(nazwaplikuocen, std::ios::trunc);
        if(plik.is_open())
        {
            std::map<int,std::shared_ptr<ocena>>::iterator ito;
            for (ito = mapaocen->begin(); ito != mapaocen->end(); ito++)
            {
                int numer = std::get<0>(*ito);
                std::shared_ptr<ocena> lok = std::get<1>(*ito);
                plik << numer << " " << lok->dajwartosc() << " ";
                int numer2;
                std::map<int,std::shared_ptr<przedmiot>>::iterator itp;
                for (itp = mapaprzedmiotow->begin(); itp != mapaprzedmiotow->end(); itp++)
                {
                    int b = std::get<0>(*itp);
                    std::shared_ptr<przedmiot> lok2 = std::get<1>(*itp);
                    if (lok2.get() == lok->dajprzedm())
                        numer2 = b;
                }
                plik << numer2 << " ";
                if (lok->dajopis() == "")
                    plik << "<pusty>" << std::endl;
                else
                    plik << lok->dajopis() << std::endl;
            }
            plik.close();
        }
        this->close();

    } else if (ui->radioButton_3->isChecked())
    {
        std::string str = ui->comboBox_3->currentText().toStdString();
        for(int i = 0; i < str.length(); i++)
        {
            if (str[i] == ':')
                str.erase(i, str.length()-i);
        }
        int ind = std::stoi(str);
        mapaprzedmiotow->erase(ind);
        std::ofstream plik;
        plik.open(nazwaplikuprzed, std::ios::trunc);
        if(plik.is_open())
        {
            std::map<int,std::shared_ptr<przedmiot>>::iterator itp;
            for (itp = mapaprzedmiotow->begin(); itp != mapaprzedmiotow->end(); itp++)
            {
                int numer = std::get<0>(*itp);
                std::shared_ptr<przedmiot> lok = std::get<1>(*itp);
                plik << numer << " " << lok->dajnazwe() << " " << lok->dajprowadzacego() << " " << lok->dajECTS() << " ";
                if (lok->dajopis() == "")
                    plik << "<pusty>" << std::endl;
                else
                    plik << lok->dajopis() << std::endl;

            }
            plik.close();
        }

    } else if (ui->radioButton_4->isChecked())
    {
        std::string str = ui->comboBox_4->currentText().toStdString();
        for(int i = 0; i < str.length(); i++)
        {
            if (str[i] == ':')
                str.erase(i, str.length()-i);
        }
        int ind = std::stoi(str);
        mapawydarzen->erase(ind);
        std::ofstream plik;
        plik.open(nazwaplikuwydarzen, std::ios::trunc);
        if(plik.is_open())
        {
            std::map<int,std::shared_ptr<wydarzenie>>::iterator itw;
            for (itw = mapawydarzen->begin(); itw != mapawydarzen->end(); itw++)
            {
                int numer = std::get<0>(*itw);
                std::shared_ptr<wydarzenie> lok = std::get<1>(*itw);
                plik << numer << " " << lok->dajdate() << " " << lok->dajnazwe() << " " ;
                std::string str2 = typeid(*(lok.get())).name();
                str2.erase(0, 6);
                plik << str2 << " ";
                if (str2 == "inne")
                    plik << -1 << " ";
                else
                {
                    int numer2;
                    std::map<int,std::shared_ptr<przedmiot>>::iterator itp;
                    for (itp = mapaprzedmiotow->begin(); itp != mapaprzedmiotow->end(); itp++)
                    {
                        int b = std::get<0>(*itp);
                        std::shared_ptr<przedmiot> lok2 = std::get<1>(*itp);
                        if (lok2.get() == lok->dajprzedm())
                            numer2 = b;
                    }
                    plik << numer2 << " ";
                }

                if (lok->dajopis() == "")
                    plik << "<pusty>" << std::endl;
                else
                    plik << lok->dajopis() << std::endl;
            }
            plik.close();
        }
        this->close();
    } else if (ui->radioButton_5->isChecked())
    {
        std::string str = ui->comboBox_5->currentText().toStdString();
        for(int i = 0; i < str.length(); i++)
        {
            if (str[i] == ':')
                str.erase(i, str.length()-i);
        }
        int ind = std::stoi(str);
        mapazajec->erase(ind);
        std::ofstream plik;
        plik.open(nazwaplikuzaj, std::ios::trunc);
        if(plik.is_open())
        {
            std::map<int,std::shared_ptr<zajecia>>::iterator itz;
            for (itz = mapazajec->begin(); itz != mapazajec->end(); itz++)
            {
                int numer = std::get<0>(*itz);
                std::shared_ptr<zajecia> lok = std::get<1>(*itz);
                plik << numer << " " ;
                std::string str2 = typeid(*(lok.get())).name();
                str2.erase(0, 6);
                plik << str2 << " ";

                    int numer2;
                    std::map<int,std::shared_ptr<przedmiot>>::iterator itp;
                    for (itp = mapaprzedmiotow->begin(); itp != mapaprzedmiotow->end(); itp++)
                    {
                        int b = std::get<0>(*itp);
                        std::shared_ptr<przedmiot> lok2 = std::get<1>(*itp);
                        if (lok2.get() == lok->dajprzedm())
                            numer2 = b;
                    }
                    plik << numer2 << " ";
                plik << lok->dajdaty().size() ;
                for (int i = 0; i < lok->dajdaty().size(); i++)
                {
                    plik << " " << lok->dajdaty().at(i);
                }
                plik << std::endl;
            }
            plik.close();
        }
        this->close();
    } else
    {

    }
}

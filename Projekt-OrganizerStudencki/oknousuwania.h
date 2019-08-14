#ifndef OKNOUSUWANIA_H
#define OKNOUSUWANIA_H

#include <QDialog>
#include <memory>
#include "alarm.h"
#include "ocena.h"
#include "przedmiot.h"
#include "wydarzenie.h"
#include "zajecia.h"
namespace Ui {
class oknousuwania;
}

class oknousuwania : public QDialog
{
    Q_OBJECT

public:
    explicit oknousuwania(QWidget *parent = 0);
    explicit oknousuwania(const std::shared_ptr<std::vector<alarm>> &,
                          const std::shared_ptr<std::map<int,std::shared_ptr<ocena>>> &,
                          const std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> &,
                          const std::shared_ptr<std::map<int,std::shared_ptr<wydarzenie>>>& wydarzenia,
                          const std::shared_ptr<std::map<int,std::shared_ptr<zajecia>>> & zajecia,
                          std::string, std::string, std::string, std::string, std::string);
    ~oknousuwania();    //klasa do obslugi okna usuwania, dostaje wszystkie dost kontenery (wskaźniki) i nazwy plikow

private slots:
    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);//metoody do obslugi ui

    void on_radioButton_4_toggled(bool checked);

    void on_radioButton_5_toggled(bool checked);

    void on_pushButton_clicked();

private:
    Ui::oknousuwania *ui;
    std::shared_ptr<std::vector<alarm>> wektoralarmow;
    std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> mapaprzedmiotow;  //wskaźniki na kontenery
    std::shared_ptr<std::map<int,std::shared_ptr<zajecia>>> mapazajec;
    std::shared_ptr<std::map<int,std::shared_ptr<wydarzenie>>> mapawydarzen;
    std::shared_ptr<std::map<int,std::shared_ptr<ocena>>> mapaocen;
    std::string nazwaplikualarmow;
    std::string nazwaplikuwydarzen; //nazwyprzedmiotow
    std::string nazwaplikuprzed;
    std::string nazwaplikuzaj;
    std::string nazwaplikuocen;
};

#endif // OKNOUSUWANIA_H

#ifndef OKNOZAJEC_H
#define OKNOZAJEC_H
#include <QMessageBox>
#include <QDialog>
#include <memory>
#include "zajecia.h"

namespace Ui {
class oknozajec;
}

class oknozajec : public QDialog
{
    Q_OBJECT

public:
    explicit oknozajec(QWidget *parent = 0);
    explicit oknozajec(std::shared_ptr<std::map<int,std::shared_ptr<zajecia>>> _mapazajec,
                       std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> _mapaprzedmiotow, int*, std::string);
    ~oknozajec(); //klasa do obslugi okna zajec, dostaje wskaźniki na kontenery i numerator oraz nazwe pliku

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();   //metody do obslugi ui

    void on_pushButton_clicked();

private:
    Ui::oknozajec *ui;
    std::vector<time_t> daty;   //pomocniczy wektor dat
    std::unique_ptr<QMessageBox> okienko;   //wskaźniki na okienko i kontenery
    std::shared_ptr<std::map<int,std::shared_ptr<zajecia>>> mapazajec;
    std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> mapaprzedmiotow;
    int *numerator;
    std::string nazwapliku;
};

#endif // OKNOZAJEC_H

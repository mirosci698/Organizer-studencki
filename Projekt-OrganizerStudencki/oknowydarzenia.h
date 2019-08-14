#ifndef OKNOWYDARZENIA_H
#define OKNOWYDARZENIA_H

#include <QDialog>
#include <memory>
#include "wydarzenie.h"
#include <QMessageBox>
namespace Ui {
class oknowydarzenia;
}

class oknowydarzenia : public QDialog
{
    Q_OBJECT

public:
    explicit oknowydarzenia(QWidget *parent = 0);
    explicit oknowydarzenia(std::shared_ptr<std::map<int,std::shared_ptr<wydarzenie>>> _mapawydarzen,
                            std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> _mapaprzedmiotow,
                            std::string, int*);
    ~oknowydarzenia(); //klasa do obslugi okna wydarzenia, dostaje wskaźniki na kontenery, nazwepliku i numerator

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted(); //metody do obslugi ui

    void on_radioButton_4_toggled(bool checked);

private:
    Ui::oknowydarzenia *ui;
    std::unique_ptr<QMessageBox> okienko;
    std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> mapaprzedmiotow;
    std::shared_ptr<std::map<int,std::shared_ptr<wydarzenie>>> mapawydarzen;
    std::string nazwapliku;
    int* numerator;
};

#endif // OKNOWYDARZENIA_H

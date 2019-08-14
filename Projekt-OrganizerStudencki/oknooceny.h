#ifndef OKNOOCENY_H
#define OKNOOCENY_H
#include <QMessageBox>
#include <QDialog>
#include <memory>
#include "ocena.h"
namespace Ui {
class oknooceny;
}

class oknooceny : public QDialog
{
    Q_OBJECT

public:
    explicit oknooceny(QWidget *parent = 0);    //klasa do obsługi okna ocen, otrzymuje wskaźniki do odpowiednich kontenerów
    //i nazwe pliku oraz wskaźnik do numeratora
    explicit oknooceny(std::shared_ptr<std::map<int,std::shared_ptr<ocena>>>,
                       std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>>,
                       int* , std::string);
    ~oknooceny();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();   //metody do obsługi ui

    void on_comboBox_currentIndexChanged(int index);

    void on_checkBox_toggled(bool checked);

private:
    Ui::oknooceny *ui;
    std::unique_ptr<QMessageBox> okienko;
    std::shared_ptr<std::map<int,std::shared_ptr<ocena>>> mapaocen; //wskaźniki na kontenery i okienko
    std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> mapaprzedmiotow;
    int* numerator;
    std::string nazwapliku;
};

#endif // OKNOOCENY_H

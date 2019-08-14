#ifndef OKNOPRZEDMIOTU_H
#define OKNOPRZEDMIOTU_H

#include <QDialog>
#include <memory>
#include <przedmiot.h>
#include <QMessageBox>
namespace Ui {
class oknoprzedmiotu;
}

class oknoprzedmiotu : public QDialog
{
    Q_OBJECT

public:
    explicit oknoprzedmiotu(QWidget *parent = 0);
    explicit oknoprzedmiotu(std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> _mapaprzedmiotow, int*);
    ~oknoprzedmiotu(); //klasa do obsługi okna przedmiotu, otrzymuje kontener z przedmiotami i wskaźnik do numeratora

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::oknoprzedmiotu *ui;
    std::unique_ptr<QMessageBox> okienko; //wskaźniki na MB i kontener z przedmiotami
    std::shared_ptr<std::map<int,std::shared_ptr<przedmiot>>> mapaprzedmiotow;
    int* numerator;
};

#endif // OKNOPRZEDMIOTU_H

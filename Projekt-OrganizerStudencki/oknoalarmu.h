#ifndef OKNOALARMU_H
#define OKNOALARMU_H
#include <QMediaPlayer>
#include <QDialog>
#include <QMessageBox>
#include <memory>
#include "alarm.h"
namespace Ui {
class oknoalarmu;
}

class oknoalarmu : public QDialog
{
    Q_OBJECT

public:
    explicit oknoalarmu(QWidget *parent = 0);
    explicit oknoalarmu(std::shared_ptr<std::vector<alarm>>, int nrusera, std::string _nazwapliku);
    ~oknoalarmu();  //klasa do obsługi okna alarmów, musi mieć wskaźnik do odp kontenera, numer i nazwe pliku usera

private slots:

    void on_przyciski_accepted();

    void on_przyciski_rejected();   //metody Qt do obsługi przycisków

    void on_glosnosc_sliderReleased();

private:
    Ui::oknoalarmu *ui;
    std::shared_ptr<std::vector<alarm>> alarmy; //wskaźniki do konteneru i MBox
    std::unique_ptr<QMessageBox> okienko;
    std::string nazwapliku;
};

#endif // OKNOALARMU_H

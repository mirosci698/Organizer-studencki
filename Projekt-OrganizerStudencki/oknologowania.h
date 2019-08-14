#ifndef OKNOLOGOWANIA_H
#define OKNOLOGOWANIA_H
#include "profil.h"
#include <QMainWindow>
#include <memory>
#include <QMessageBox>
namespace Ui {
class OknoLogowania;
}

class OknoLogowania : public QMainWindow
{
    Q_OBJECT

public:
    explicit OknoLogowania(QWidget *parent = 0);
    explicit OknoLogowania(int*);
    ~OknoLogowania();

private slots:
    void on_przycisklogowania_clicked();
//metody do obsługi ui
    void on_przycisknowegokonta_clicked();

private:
    Ui::OknoLogowania *ui;
    std::shared_ptr<std::vector<profil>> profile;   //kontener profili
    std::unique_ptr<QMessageBox> okienko; //okienka komunikatu jako messageboxy
    int * nrprofilu; //jedynie adres, nic tu nie alokujemy, można usunąć
};

#endif // OKNOLOGOWANIA_H

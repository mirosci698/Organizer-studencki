#ifndef PROFIL_H
#define PROFIL_H
#include <iostream>
class profil //klasa do obslugi profili uzytkownika
{
    std::string login;
    int ID;
    std::string haslo;
    static int przydzial;   //numerator - nadaje id
public:
    profil(std::string, std::string);
    static std::string zaszyfruj(const std::string &); //metoda klasy do szyfrowania
    bool sprawdzlogin(const std::string &);
    bool sprawdzhaslo(const std::string &);
    int dajID();
    std::string dajlogin();
    std::string dajhaslo();
    void static wpiszprzyd(int); //wpis do statica
    ~profil();
};
#endif // PROFIL_H

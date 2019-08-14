#ifndef PRZEDMIOT_H
#define PRZEDMIOT_H
#include <iostream>
class przedmiot
{
    std::string nazwa;
    std::string nazwisko;
    std::string imie;
    int ECTS;
    std::string uwagi;
public:
    przedmiot(std::string, std::string, std::string, int);
    przedmiot(std::string, std::string, std::string, int, std::string);
    std::string dajnazwe();
    std::string dajprowadzacego();
    std::string dajopis();
    int dajECTS();
    ~przedmiot();
};
#endif // PRZEDMIOT_H

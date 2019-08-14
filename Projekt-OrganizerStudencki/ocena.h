#ifndef OCENA_H
#define OCENA_H
#include <iostream>

#include "przedmiot.h"
class ocena
{
    double wartosc;
    przedmiot* przedm; //pola te są jedynie odnośnikami
    std::string opis;
public:

    ocena(double, przedmiot*);
    ocena(double, przedmiot*, std::string);
    double dajwartosc();
    przedmiot* dajprzedm(); //pola te są jedynie odnośnikami
    std::string dajopis();
    ~ocena();
};
#endif // OCENA_H

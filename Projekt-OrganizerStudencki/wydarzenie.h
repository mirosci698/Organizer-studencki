#ifndef WYDARZENIE_H
#define WYDARZENIE_H
#include <iostream>
#include <ctime>
#include "przedmiot.h"
class wydarzenie
{
public:
    time_t data;
    std::string nazwa;
    std::string opis;
public:
    wydarzenie(time_t, std::string);
    wydarzenie(time_t, std::string, std::string);
    time_t dajdate();
    std::string dajnazwe();
    std::string dajopis();
    virtual przedmiot* dajprzedm();
    virtual ~wydarzenie();
};
class kartkowka: public wydarzenie
{
    przedmiot* przedm;
public:
    kartkowka(time_t, std::string, przedmiot*);
    kartkowka(time_t, std::string, std::string, przedmiot*);
    przedmiot* dajprzedm();
    ~kartkowka();
};
class kolokwium: public wydarzenie
{
    przedmiot* przedm;
public:
    kolokwium(time_t, std::string, przedmiot*);
    kolokwium(time_t, std::string, std::string, przedmiot*);
    przedmiot* dajprzedm();
    ~kolokwium();
};
class egzamin: public wydarzenie
{
    przedmiot* przedm;
public:
    egzamin(time_t, std::string, przedmiot*);
    egzamin(time_t, std::string, std::string, przedmiot*);
    przedmiot* dajprzedm();
    ~egzamin();
};
class inne: public wydarzenie
{
public:
    inne(time_t, std::string);
    inne(time_t, std::string, std::string);
    ~inne();
};
#endif // WYDARZENIE_H

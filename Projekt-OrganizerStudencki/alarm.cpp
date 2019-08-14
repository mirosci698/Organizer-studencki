#include "alarm.h"

alarm::alarm(time_t ldata, int ldzwiek, int lglosnosc):dzwiek(ldzwiek), glosnosc(lglosnosc)
{
    time_t aktualnyczas;//=time(NULL); - też da radę
    time(&aktualnyczas);
    if (difftime(ldata, aktualnyczas) < 0)
        throw std::logic_error("data"); //sprawdzanie daty czy nie jest przeszła
    if (ldzwiek != 0 && ldzwiek != 1 && ldzwiek != 2)
        throw std::exception(); //odp rodzaj dzwieku i czestotliwosc
    if (lglosnosc < 0 || lglosnosc > 100)
        throw std::exception();
    datawyd = ldata;
}
time_t alarm::dajdate() //gettery
{
    return datawyd;
}
int alarm::dajdzwiek()
{
    return dzwiek;
}
int alarm::dajglosnosc()
{
    return glosnosc;
}
bool alarm::sprawdzmoment(const time_t &spr) //porownanie czasu
{

    return  datawyd == spr;
}

alarm::~alarm()
{
}

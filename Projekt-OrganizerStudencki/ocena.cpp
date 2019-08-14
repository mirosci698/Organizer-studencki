#include "ocena.h"

ocena::ocena(double lwartosc, przedmiot* lprzedm):wartosc(lwartosc), przedm(lprzedm)
{
    if (lwartosc < 2.0 || lwartosc > 5.0)
        throw std::exception();
    if (lprzedm == nullptr)
        throw std::exception();
    opis = "";
}
ocena::ocena(double lwartosc, przedmiot* lprzedm, std::string lopis):wartosc(lwartosc), przedm(lprzedm), opis(lopis)
{
    if (lwartosc < 2.0 || lwartosc > 5.0)
        throw std::exception();
    if (lprzedm == nullptr)
        throw std::exception();
}
przedmiot* ocena::dajprzedm()
{
    return przedm;
}
double ocena::dajwartosc()
{
    return wartosc;
}

std::string ocena::dajopis()
{
    return opis;
}
ocena::~ocena()
{

}

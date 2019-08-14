#include "przedmiot.h"
przedmiot::przedmiot(std::string lnazwa, std::string lnazwisko, std::string limie, int lECTS):
    nazwa(lnazwa), nazwisko(lnazwisko), imie(limie), ECTS(lECTS)
{
    if(limie.length()== 0 || lnazwisko.length()==0 || lnazwa.length() == 0)
        throw std::exception();
    if(lECTS < 0 || lECTS > 30)
        throw std::exception();
    uwagi="";
}
przedmiot::przedmiot(std::string lnazwa, std::string lnazwisko, std::string limie, int lECTS, std::string luwagi):
    nazwa(lnazwa), nazwisko(lnazwisko), imie(limie), ECTS(lECTS), uwagi(luwagi)
{
    if(limie.length()== 0 || lnazwisko.length()==0 || /*luwagi.length() == 0 ||*/ lnazwa.length() == 0)
        throw std::exception();
    if(lECTS < 0 || lECTS > 30)
        throw std::exception();
}
std::string przedmiot::dajnazwe()
{
    return nazwa;
}
std::string przedmiot::dajprowadzacego()
{
    return nazwisko + " " + imie;
}
std::string przedmiot::dajopis()
{
    return uwagi;
}
int przedmiot::dajECTS()
{
   return ECTS;
}

przedmiot::~przedmiot()
{

}

#include "profil.h"
#define KLUCZ 17
profil::profil(std::string llogin, std::string lhaslo):
    login(llogin), haslo(lhaslo)
{
    przydzial++;
    if(llogin.length()==0)
        throw std::exception(); //rzucanie wyjątków gdy nie ma loginu lub hasla
    if(lhaslo.length()==0)  //czesc warunkow do tworzenia profili w samym oknie logowania zeby mozna je bylo lepiej okreslac
        throw std::exception();
    ID = przydzial;
}
std::string profil::zaszyfruj(const std::string & zmieniane) //statyczna zeby brala ten sam klucz
{
    std::string wynik = zmieniane;
    for (int i = 0; i < wynik.length(); i++)
    {
        wynik[i] = wynik[i] ^ KLUCZ; //prosty szyfr xor ze zdefiniowanym kluczem
    }
    return wynik;
}
bool profil::sprawdzlogin(const std::string & log)  //porownywania
{
    return (login==log);
}
bool profil::sprawdzhaslo(const std::string & has)
{
    return (haslo==has);
}
int profil::dajID() //gettery
{
    return ID;
}
std::string profil::dajlogin()
{
    return login;
}
std::string profil::dajhaslo()
{
    return haslo;
}
void profil::wpiszprzyd(int wpisywany)
{
    przydzial = wpisywany;
}

profil::~profil()
{

}
int profil::przydzial=0; //poczatkowa wartosc statica

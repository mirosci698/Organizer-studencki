#include "wydarzenie.h"
wydarzenie::wydarzenie(time_t ldata, std::string lnazwa):data(ldata), nazwa(lnazwa)
{
    time_t aktualnyczas;//=time(NULL); - też da radę
    time(&aktualnyczas);
    //time_t sekundy = mktime(&ldata);
    if (difftime(ldata, aktualnyczas) <= 0)
        throw std::logic_error("data");
    if(lnazwa.length() == 0)
        throw std::exception();
    opis = "";
}
wydarzenie::wydarzenie(time_t ldata, std::string lnazwa, std::string lopis): data(ldata), nazwa(lnazwa), opis(lopis)
{
    time_t aktualnyczas;//=time(NULL); - też da radę
    time(&aktualnyczas);
   // time_t sekundy = mktime(&ldata);
    if (difftime(ldata, aktualnyczas) <= 0)
        throw std::logic_error("data");
    if(lnazwa.length() == 0)
        throw std::exception();
}
time_t wydarzenie::dajdate()
{
    return data;
}
std::string wydarzenie::dajnazwe()
{
    return nazwa;
}
std::string wydarzenie::dajopis()
{
    return opis;
}
przedmiot* wydarzenie::dajprzedm()
{
    return NULL;
}

wydarzenie::~wydarzenie()
{

}
kartkowka::kartkowka(time_t ldata, std::string lnazwa, przedmiot* lprzedmiot): wydarzenie(ldata, lnazwa), przedm(lprzedmiot)
{
    if(lprzedmiot == nullptr)
        throw std::exception();
}
kartkowka::kartkowka(time_t ldata, std::string lnazwa, std::string lopis, przedmiot* lprzedmiot): wydarzenie(ldata, lnazwa, lopis), przedm(lprzedmiot)
{
    if(lprzedmiot == nullptr)
        throw std::exception();
}
kartkowka::~kartkowka()
{

}
kolokwium::kolokwium(time_t ldata, std::string lnazwa, przedmiot* lprzedmiot): wydarzenie(ldata, lnazwa), przedm(lprzedmiot)
{
    if(lprzedmiot == nullptr)
        throw std::exception();
}
kolokwium::kolokwium(time_t ldata, std::string lnazwa, std::string lopis, przedmiot* lprzedmiot): wydarzenie(ldata, lnazwa, lopis), przedm(lprzedmiot)
{
    if(lprzedmiot == nullptr)
        throw std::exception();
}
kolokwium::~kolokwium()
{

}
egzamin::egzamin(time_t ldata, std::string lnazwa, przedmiot* lprzedmiot): wydarzenie(ldata, lnazwa), przedm(lprzedmiot)
{
    if(lprzedmiot == nullptr)
        throw std::exception();
}
egzamin::egzamin(time_t ldata, std::string lnazwa, std::string lopis, przedmiot* lprzedmiot): wydarzenie(ldata, lnazwa, lopis), przedm(lprzedmiot)
{
    if(lprzedmiot == nullptr)
        throw std::exception();
}
egzamin::~egzamin()
{

}
inne::inne(time_t ldata, std::string lnazwa): wydarzenie(ldata, lnazwa)
{

}
inne::inne(time_t ldata, std::string lnazwa, std::string lopis): wydarzenie(ldata, lnazwa, lopis)
{

}
inne::~inne()
{

}
przedmiot* kartkowka::dajprzedm()
{
    return przedm;
}
przedmiot* kolokwium::dajprzedm()
{
    return przedm;
}
przedmiot* egzamin::dajprzedm()
{
    return przedm;
}

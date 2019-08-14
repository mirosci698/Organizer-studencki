#include "zajecia.h"
zajecia::zajecia(przedmiot* lprzedmiot): przedm(lprzedmiot)
{
    if(lprzedmiot == nullptr)
        throw std::exception();
}
void zajecia::wpiszdaty(std::vector<time_t> _daty)
{
    daty = _daty;
}
std::vector<time_t> zajecia::dajdaty()
{
    return daty;
}
przedmiot* zajecia::dajprzedm()
{
    return przedm;
}

zajecia::~zajecia()
{

}
wyklad::wyklad(przedmiot* lprzedmiot): zajecia(lprzedmiot)
{

}
wyklad::~wyklad()
{

}
laboratorium::laboratorium(przedmiot* lprzedmiot): zajecia(lprzedmiot)
{

}
laboratorium::~laboratorium()
{

}
cwiczenia::cwiczenia(przedmiot* lprzedmiot): zajecia(lprzedmiot)
{

}
cwiczenia::~cwiczenia()
{

}
projekt::projekt(przedmiot* lprzedmiot): zajecia(lprzedmiot)
{

}
projekt::~projekt()
{

}
seminarium::seminarium(przedmiot* lprzedmiot): zajecia(lprzedmiot)
{

}
seminarium::~seminarium()
{

}
praktyka::praktyka(przedmiot* lprzedmiot): zajecia(lprzedmiot)
{

}
praktyka::~praktyka()
{

}

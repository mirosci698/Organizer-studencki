#include "konfig.h"
#include <iostream>
konfig::konfig(std::string nazwa)
{
    try {
        plik.open(nazwa);
        if  (!plik.is_open())
            throw 1;
        int IDplik;
        plik >> IDplik;
        std::cout << IDplik;
    }
    catch (...)
    {
            std::cout << "Blad";
    }

}

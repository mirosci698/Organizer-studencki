#ifndef ZAJECIA_H
#define ZAJECIA_H
#include <vector>
#include <QDateTime>
#include "przedmiot.h"
class zajecia
{
    przedmiot* przedm;
    std::vector<time_t> daty;
public:
    zajecia(przedmiot*);
    void wpiszdaty(std::vector<time_t> _daty);
    std::vector<time_t> dajdaty();
    przedmiot* dajprzedm();
    virtual ~zajecia();
};
class wyklad: public zajecia
{
public:
    wyklad(przedmiot*);
    ~wyklad();
};
class laboratorium: public zajecia
{
public:
    laboratorium(przedmiot*);
    ~laboratorium();
};
class cwiczenia: public zajecia
{
public:
    cwiczenia(przedmiot*);
    ~cwiczenia();
};
class projekt: public zajecia
{
public:
    projekt(przedmiot*);
    ~projekt();
};
class seminarium: public zajecia
{
public:
    seminarium(przedmiot*);
    ~seminarium();
};
class praktyka: public zajecia
{
public:
    praktyka(przedmiot*);
    ~praktyka();
};
#endif // ZAJECIA_H

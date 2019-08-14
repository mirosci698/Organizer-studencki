#ifndef ALARM_H
#define ALARM_H
#include <ctime>
#include <iostream>
class alarm
{
    time_t datawyd;
    int dzwiek; //klasa do obsługi alarmów
    int glosnosc;
public:
    alarm(time_t, int, int);
    time_t dajdate();
    int dajdzwiek();
    int dajglosnosc();
    bool sprawdzmoment(const time_t &);
    ~alarm();
};
#endif // ALARM_H

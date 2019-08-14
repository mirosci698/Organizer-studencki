#ifndef KONFIG_H
#define KONFIG_H
#include <fstream>
class konfig // spróbować zrobić singleton
{
    std::fstream plik;
public:
    konfig(std::string);
};
#endif // KONFIG_H

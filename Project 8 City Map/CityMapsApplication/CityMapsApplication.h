#ifndef __Application_H
#define __Application_H

#include "../CityMaps/CityMaps.h"

class CityMapsApplication
{
public:
    CityMapsApplication() : initiated{false} {};

    void deserialize(const std::string &);
    void location();
    void neighbours();
    void move(const std::string &);
    void close(const std::string &);
    void open(const std::string &);
    void closed();
    void tour();
    void start();

private:
    CityMaps<std::string, int> currLoadedCity;
    bool initiated;
};

#include "CityMapsApplication.cpp"
#endif

#ifndef MOTORCYLE_H
#define MOTORCYLE_H

#include <iostream>
#include <cstring>
#include <iomanip>
#include "Vehicle.h"

using namespace std;

namespace sdds
{
    class Motorcycle : public Vehicle
    {
    private:
        bool sideCar;

    public:
        Motorcycle();
        Motorcycle(const char *lic, const char *make);
        Motorcycle &operator=(const Motorcycle &) = delete;
        Motorcycle(const Motorcycle &) = delete;
        istream &read(istream &istr = cin);
        ostream &write(ostream &ostr = cout) const;
    };
} // namespace sdds

#endif
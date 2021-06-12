#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <cstring>
#include <iomanip>
#include "Vehicle.h"

using namespace std;

namespace sdds
{
    class Car : public Vehicle
    {
    private:
        bool carWash;

    public:
        Car();
        Car(const char *lic, const char *make);
        Car &operator=(const Car &) = delete;
        Car(const Car &) = delete;
        istream &read(istream &istr = cin);
        ostream &write(ostream &ostr = cout) const;
    };
} // namespace sdds

#endif
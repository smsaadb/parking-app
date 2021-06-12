#ifndef VEHICLE
#define VEHICLE

#include <iostream>
#include <cstring>
#include "ReadWritable.h"

using namespace std;

namespace sdds
{
    class Vehicle : public ReadWritable
    {
    protected:
        char licPlate[9];
        char *makeModel;
        int spotNum;

        void setEmpty();
        bool isEmpty() const;
        void setMakeModel(const char *make);

    public:
        char *getLicensePlate();
        char *getMakeModel() const;
        Vehicle();
        Vehicle(const char *lic, const char *make);
        Vehicle(const Vehicle &) = delete;
        Vehicle &operator=(const Vehicle &) = delete;
        int getParkingSpot() const;
        void setParkingSpot(int ps);
        virtual istream &read(istream &istr = cin);
        virtual ostream &write(ostream &ostr = cout) const;
        friend bool operator==(const Vehicle &v, const char *lic);
        friend bool operator==(const Vehicle &v1, const Vehicle &v2);
        ~Vehicle();
    };

} // namespace sdds

#endif

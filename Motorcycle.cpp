#include <iostream>
#include <cstring>
#include "Motorcycle.h"

using namespace std;

namespace sdds
{
    Motorcycle::Motorcycle() : Vehicle()
    {
    }

    Motorcycle::Motorcycle(const char *lic, const char *make) : Vehicle(lic, make)
    {
    }

    istream &Motorcycle::read(istream &istr)
    {
        if (isCsv())
        {
            char temp[100];
            Vehicle::read(istr);
            istr.getline(temp, 100, '\n');
            sideCar = atoi(temp);
        }
        else
        {
            cout << "\nMotorcycle information entry" << endl;
            Vehicle::read(istr);
            cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
            char response[10] = "";
            while (true)
            {
                istr.getline(response, 10, '\n');

                if ((response[0] == 'y' || response[0] == 'Y' || response[0] == 'n' || response[0] == 'N') && (response[1] == '\n' || response[1] == '\0'))
                {
                    if (response[0] == 'y' || response[0] == 'Y')
                    {
                        sideCar = true;
                    }
                    else
                    {
                        sideCar = false;
                    }

                    break;
                }
                else
                {
                    cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
                }
            }
        }
        if (!istr)
        {
            if (makeModel != nullptr)
            {
                delete[] makeModel;
            }
            Vehicle::setEmpty();
        }
        return istr;
    }

    ostream &Motorcycle::write(ostream &ostr) const
    {
        if (licPlate[0] == '\0')
        {
            ostr << "Invalid Motorcycle Object" << endl;
        }
        else
        {
            if (isCsv())
            {
                ostr << "M,";
                Vehicle::write(ostr);
                ostr << sideCar << endl;
            }
            else
            {
                ostr << "Vehicle type: Motorcycle" << endl;
                Vehicle::write(ostr);
                if (sideCar)
                {
                    ostr << "With Sidecar" << endl;
                }
            }
        }
        return ostr;
    }
} // namespace sdds
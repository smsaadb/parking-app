#include <iostream>
#include <cstring>
#include "Car.h"

using namespace std;

namespace sdds
{

    Car::Car() : Vehicle()
    {
    }

    Car::Car(const char *lic, const char *make) : Vehicle(lic, make)
    {
    }

    istream &Car::read(istream &istr)
    {
        if (isCsv())
        {
            char temp[100];
            Vehicle::read(istr);
            istr.getline(temp, 100, '\n');
            carWash = atoi(temp);
        }
        else
        {
            cout << "\nCar information entry" << endl;
            Vehicle::read(istr);
            cout << "Carwash while parked? (Y)es/(N)o: ";
            char response[10] = "";
            while (true)
            {
                istr.getline(response, 10, '\n');

                if ((response[0] == 'y' || response[0] == 'Y' || response[0] == 'n' || response[0] == 'N') && (response[1] == '\n' || response[1] == '\0'))
                {
                    if (response[0] == 'y' || response[0] == 'Y')
                    {
                        carWash = true;
                    }
                    else
                    {
                        carWash = false;
                    }

                    break;
                }
                else
                {
                    cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
                }
            }
        }
        //ms6
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

    ostream &Car::write(ostream &ostr) const
    {
        if (licPlate[0] == '\0')
        {
            ostr << "Invalid Car Object" << endl;
        }
        else
        {
            if (isCsv())
            {
                ostr << "C,";
                Vehicle::write(ostr);
                ostr << carWash << endl;
            }
            else
            {
                ostr << "Vehicle type: Car" << endl;
                Vehicle::write(ostr);
                if (carWash)
                {
                    ostr << "With Carwash" << endl;
                }
                else
                {
                    ostr << "Without Carwash" << endl;
                }
            }
        }
        return ostr;
    }

} // namespace sdds
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Vehicle.h"
#include "ReadWritable.h"
#include "Parking.h"
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace sdds
{
    Vehicle::Vehicle()
    {
        makeModel = nullptr;
        spotNum = 0;
        licPlate[0] = '\0';
    }

    Vehicle::Vehicle(const char *lic, const char *make)
    {
        if (make == nullptr || lic == nullptr || lic[0] == '\0' || strlen(lic) > 8 || strlen(make) < 2 || strlen(make) > 60)
        {
            makeModel = nullptr;
            spotNum = 0;
            licPlate[0] = '\0';
        }
        else
        {
            spotNum = 0;
            strncpy(licPlate, lic, 8);
            makeModel = new char[strlen(make) + 1];
            strcpy(makeModel, make);
        }
    }

    int Vehicle::getParkingSpot() const
    {
        return spotNum;
    }

    void Vehicle::setParkingSpot(int ps)
    {
        if (ps >= 0)
        {
            spotNum = ps;
        }
        else
        {
            setEmpty();
        }
    }

    bool operator==(const Vehicle &v, const char *lic)
    {
        bool returnValue = false;
        int i = 0;

        if (strlen(v.licPlate) != strlen(lic))
        {
            returnValue = false;
        }
        else
        {
            while (lic[i] != '\0')
            {
                if ((lic[i] >= 'A' && lic[i] <= 'Z') || (lic[i] >= 'a' && lic[i] <= 'z'))
                {
                    if (lic[i] == v.licPlate[i] || lic[i] == (v.licPlate[i] + 32) || lic[i] == (v.licPlate[i] - 32))
                    {
                        returnValue = true;
                    }
                    else
                    {
                        returnValue = false;
                        break;
                    }
                }
                else if (lic[i] >= '0' && lic[i] <= '9')
                {
                    if (lic[i] == v.licPlate[i])
                    {
                        returnValue = true;
                    }
                    else
                    {
                        returnValue = false;
                        break;
                    }
                }
                else
                {
                    returnValue = false;
                    break;
                }

                i++;
            }
        }

        return returnValue;
    }

    bool operator==(const Vehicle &v1, const Vehicle &v2)
    {
        bool returnValue = false;
        int i = 0;

        while (v1.licPlate[i] != '\0')
        {
            if ((v1.licPlate[i] >= 'A' && v1.licPlate[i] <= 'Z') || (v1.licPlate[i] >= 'a' && v1.licPlate[i] <= 'z'))
            {
                if (v1.licPlate[i] == v2.licPlate[i] || v1.licPlate[i] == (v2.licPlate[i] + 32) || v1.licPlate[i] == (v2.licPlate[i] - 32))
                {
                    returnValue = true;
                }
                else
                {
                    returnValue = false;
                    break;
                }
            }
            else if (v1.licPlate[i] >= '0' && v1.licPlate[i] <= '9')
            {
                if (v1.licPlate[i] == v2.licPlate[i])
                {
                    returnValue = true;
                }
                else
                {
                    returnValue = false;
                    break;
                }
            }
            else
            {
                returnValue = false;
                break;
            }

            i++;
        }

        return returnValue;
    }

    istream &Vehicle::read(istream &istr)
    {

        if (makeModel != nullptr)
        {
            delete[] makeModel;
            makeModel = nullptr;
        }

        if (isCsv())
        {
            char temp[9] = "";
            char mtemp[61] = "";

            istr.getline(temp, 9, ',');
            spotNum = atoi(temp);

            istr.getline(temp, 9, ',');
            int i = 0;
            while (temp[i] != '\0')
            {
                if (temp[i] >= 'a' && temp[i] <= 'z')
                {
                    temp[i] -= 32;
                }
                i++;
            }
            strcpy(licPlate, temp);
            istr.getline(mtemp, 61, ',');
            makeModel = new char[strlen(mtemp) + 1];
            strcpy(makeModel, mtemp);
        }
        else
        {
            char temp1[100] = "";
            char temp2[100] = "";
            cout << "Enter Licence Plate Number: ";
            while (true)
            {
                istr.getline(temp1, 100, '\n');
                if (strlen(temp1) < 1 || strlen(temp1) > 8)
                {
                    cout << "Invalid Licence Plate, try again: ";
                }
                else
                {
                    break;
                }
            }
            int i = 0;
            while (temp1[i] != '\0')
            {
                if (temp1[i] >= 'a' && temp1[i] <= 'z')
                {
                    temp1[i] -= 32;
                }
                i++;
            }
            strcpy(licPlate, temp1);

            cout << "Enter Make and Model: ";
            while (true)
            {
                istr.getline(temp2, 100, '\n');
                if (strlen(temp2) < 2 || strlen(temp2) > 60)
                {
                    cout << "Invalid Make and model, try again: ";
                }
                else
                {
                    break;
                }
            }
            makeModel = new char[strlen(temp2) + 1];
            strcpy(makeModel, temp2);
        }

        if (!istr)
        {
            if (makeModel != nullptr)
            {
                delete[] makeModel;
            }
            setEmpty();
        }

        return istr;
    }

    ostream &Vehicle::write(ostream &ostr) const
    {
        if (licPlate[0] == '\0')
        {
            ostr << "Invalid Vehicle Object" << endl;
        }
        else
        {
            if (isCsv())
            {
                ostr << spotNum << "," << licPlate << "," << makeModel << ",";
            }
            else
            {
                ostr << "Parking Spot Number: ";
                if (spotNum != 0)
                {
                    ostr << spotNum << endl;
                }
                else
                {
                    ostr << "N/A" << endl;
                }
                ostr << "Licence Plate: " << licPlate << endl;
                ostr << "Make and Model: " << makeModel << endl;
            }
        }

        return ostr;
    }

    void Vehicle::setEmpty()
    {
        licPlate[0] = '\0';
        if (makeModel != nullptr)
        {
            delete[] makeModel;
            makeModel = nullptr;
        }
        spotNum = 0;
    }

    bool Vehicle::isEmpty() const
    {
        if (licPlate[0] == '\0')
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    char *Vehicle::getLicensePlate()
    {
        return licPlate;
    }

    char *Vehicle::getMakeModel() const
    {
        return makeModel;
    }

    void Vehicle::setMakeModel(const char *make)
    {
        if (make == nullptr || make[0] == '\0')
        {
            if (makeModel != nullptr)
            {
                delete[] makeModel;
            }
            setEmpty();
        }
        else
        {
            delete[] makeModel;
            makeModel = new char[strlen(make) + 1];
            strcpy(makeModel, make);
        }
    }

    Vehicle::~Vehicle()
    {
        if (makeModel != nullptr)
        {
            delete[] makeModel;
            makeModel = nullptr;
        }
    }
} // namespace sdds
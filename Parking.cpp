#include <cstring>
#include <iostream>
#include <fstream>
#include "Parking.h"

using namespace std;

namespace sdds
{
    Parking::Parking(const char *name, int noOfSpots)
    {
        for (int i = 0; i < maxParkingSpots; i++)
        {
            parkingSpots[i] = nullptr;
        }

        if (name != nullptr && name[0] != '\0' && (noOfSpots >= 10 && noOfSpots <= maxParkingSpots))
        {
            filename = new char[strlen(name) + 1];
            strcpy(filename, name);
            numOfSpots = noOfSpots;
            parkedVehicles = 0;
        }
        else
        {
            filename = nullptr;
            numOfSpots = 0;
            parkedVehicles = 0;
        }

        if (loadDataFile())
        {
            mainMenu = new Menu("Parking Menu, select an action:");
            vehicleMenu = new Menu("Select type of the vehicle:", 1);

            *mainMenu << "Park Vehicle"
                      << "Return Vehicle"
                      << "List Parked Vehicles"
                      << "Close Parking (End of day)"
                      << "Exit Program";

            *vehicleMenu << "Car"
                         << "Motorcycle"
                         << "Cancel";
        }
        else
        {
            mainMenu = nullptr;
            vehicleMenu = nullptr;
            cout << "Error in data file" << endl;
        }
    }

    Parking::~Parking()
    {
        saveDataFile();
        if (filename != nullptr)
        {
            delete[] filename;
            filename = nullptr;
        }

        if (mainMenu != nullptr)
        {
            delete mainMenu;
            mainMenu = nullptr;
        }

        if (vehicleMenu != nullptr)
        {
            delete vehicleMenu;
            vehicleMenu = nullptr;
        }
        for (int i = 0; i < numOfSpots; i++)
        {
            if (parkingSpots[i] != nullptr)
            {
                delete parkingSpots[i];
                parkingSpots[i] = nullptr;
            }
        }
    }

    bool Parking::isEmpty() const
    {
        if (filename == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Parking::parkingStatus() const
    {
        cout << "****** Seneca Valet Parking ******" << endl;
        cout << "*****  Available spots: ";
        cout << left << setw(4) << numOfSpots - parkedVehicles;
        cout << " *****" << endl;
    }

    void Parking::vehicleSelection()
    {
        if (parkedVehicles == numOfSpots)
        {
            cout << "Parking is full" << endl;
        }
        else
        {
            switch (vehicleMenu->run())
            {
            case 1:
            {
                Car *c = new Car();
                c->setCsv(false);
                c->read();
                for (int i = 0; i < numOfSpots; i++)
                {
                    if (parkingSpots[i] == nullptr)
                    {
                        c->setParkingSpot(i + 1);
                        cout << "\nParking Ticket" << endl;
                        c->write();
                        cout << endl;
                        parkingSpots[i] = c;
                        parkedVehicles++;
                        break;
                    }
                }
            }
            break;

            case 2:
            {
                Motorcycle *m = new Motorcycle();
                m->setCsv(false);
                m->read();
                for (int i = 0; i < numOfSpots; i++)
                {
                    if (parkingSpots[i] == nullptr)
                    {
                        m->setParkingSpot(i + 1);
                        cout << "\nParking Ticket" << endl;
                        m->write();
                        cout << endl;
                        parkingSpots[i] = m;
                        parkedVehicles++;
                        break;
                    }
                }
            }
            break;

            case 3:
                cout << "Parking cancelled" << endl;
                break;
            }
        }
    }

    void Parking::returnVehicle()
    {
        int foundIndex = -1;
        cout << "Return Vehicle" << endl;
        char lic[100] = "";
        cout << "Enter Licence Plate Number: ";
        while (true)
        {
            cin.getline(lic, 100, '\n');
            if (strlen(lic) < 1 || strlen(lic) > 8)
            {
                cout << "Invalid Licence Plate, try again: ";
            }
            else
            {
                break;
            }
        }

        for (int i = 0; i < numOfSpots; i++)
        {
            if (parkingSpots[i] != nullptr)
            {
                if (*parkingSpots[i] == lic)
                {
                    foundIndex = i;
                    break;
                }
            }
        }
        if (foundIndex != -1)
        {
            cout << "\nReturning: " << endl;
            parkingSpots[foundIndex]->setCsv(false);
            parkingSpots[foundIndex]->write();
            cout << endl;
            delete parkingSpots[foundIndex];
            parkingSpots[foundIndex] = nullptr;
            parkedVehicles--;
        }
        else
        {
            cout << "Licence plate " << lic << " Not found" << endl;
        }
    }

    void Parking::listVehicles() const
    {
        cout << "*** List of parked vehicles ***" << endl;
        for (int i = 0; i < numOfSpots; i++)
        {
            if (parkingSpots[i] != nullptr)
            {
                parkingSpots[i]->setCsv(false);
                parkingSpots[i]->write();
                cout << "-------------------------------" << endl;
            }
        }
    }

    bool Parking::closeParking()
    {
        if (parkedVehicles == 0)
        {
            cout << "\nClosing Parking" << endl;
            return true;
        }
        else
        {
            bool confirm = false;
            cout << "This will Remove and tow all remaining vehicles from the parking!" << endl;
            cout << "Are you sure? (Y)es/(N)o: ";

            char response[10] = "";
            while (true)
            {
                cin.getline(response, 10, '\n');

                if ((response[0] == 'y' || response[0] == 'Y' || response[0] == 'n' || response[0] == 'N') && (response[1] == '\n' || response[1] == '\0'))
                {
                    if (response[0] == 'y' || response[0] == 'Y')
                    {
                        confirm = true;
                    }
                    else
                    {
                        confirm = false;
                    }

                    break;
                }
                else
                {
                    cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
                }
            }

            if (!confirm)
            {
                cout << "Aborted!" << endl;
                return false;
            }
            else
            {
                cout << "Closing Parking"
                     << endl;
                for (int i = 0; i < numOfSpots; i++)
                {
                    if (parkingSpots[i] != nullptr)
                    {
                        cout << "\nTowing request" << endl;
                        cout << "*********************" << endl;
                        parkingSpots[i]->write();
                        delete parkingSpots[i];
                        parkingSpots[i] = nullptr;
                        parkedVehicles--;
                    }
                }
                return true;
            }
        }
    }
    bool Parking::exitParking() const
    {
        char ans = 'a';
        cout << "This will terminate the program!" << endl;
        cout << "Are you sure? (Y)es/(N)o: ";
        ans = yOrN();
        if (ans == 'y' || ans == 'Y')
        {
            cout << "Exiting program!" << endl;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Parking::loadDataFile()
    {
        if (!isEmpty())
        {
            ifstream file(filename);
            char cOrM[4];
            if (file.is_open())
            {
                while (file.good())
                {
                    file.getline(cOrM, 4, ',');
                    if (cOrM[0] == 'C' || cOrM[0] == 'c')
                    {
                        Car *v = new Car();
                        v->setCsv(true);
                        v->read(file);
                        if (parkingSpots[v->getParkingSpot() - 1] != nullptr)
                        {
                            delete parkingSpots[v->getParkingSpot() - 1];
                            parkedVehicles--;
                        }
                        parkingSpots[v->getParkingSpot() - 1] = v;
                        parkedVehicles++;
                        if (parkedVehicles == numOfSpots)
                        {
                            break;
                        }
                    }
                    else if (cOrM[0] == 'M' || cOrM[0] == 'm')
                    {
                        Motorcycle *v = new Motorcycle();
                        v->setCsv(true);
                        v->read(file);
                        if (parkingSpots[v->getParkingSpot() - 1] != nullptr)
                        {
                            delete parkingSpots[v->getParkingSpot() - 1];
                            parkedVehicles--;
                        }
                        parkingSpots[v->getParkingSpot() - 1] = v;
                        parkedVehicles++;
                        if (parkedVehicles == numOfSpots)
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                cout << "File didn't open..." << endl;
            }

            return true;
        }
        else
        {
            return false;
        }
    }

    void Parking::saveDataFile() const
    {
        if (!isEmpty())
        {
            ofstream file(filename);
            for (int i = 0; i < numOfSpots; i++)
            {
                if (parkingSpots[i] != nullptr)
                {
                    parkingSpots[i]->setCsv(true);
                    parkingSpots[i]->write(file);
                }
            }
        }
    }

    int Parking::run()
    {
        if (!isEmpty())
        {
            int selection = -1;
            bool endRun = false;

            while (true)
            {
                parkingStatus();
                selection = mainMenu->run();
                switch (selection)
                {
                case 1:
                    vehicleSelection();
                    break;

                case 2:
                    returnVehicle();
                    break;

                case 3:
                    listVehicles();
                    break;

                case 4:
                    if (closeParking())
                    {
                        endRun = true;
                    }
                    break;

                case 5:
                    if (exitParking())
                    {
                        endRun = true;
                    }
                    break;

                default:
                    break;
                }

                if (endRun)
                {
                    break;
                }
            }

            return 0;
        }
        else
        {
            return 1;
        }
    }

    char Parking::yOrN() const
    {
        while (true)
        {
            char response[10] = "";
            cin >> response;
            clearBuffer();

            if ((response[0] == 'y' || response[0] == 'Y' || response[0] == 'n' || response[0] == 'N') && (response[1] == '\n' || response[1] == '\0'))
            {
                return response[0];
                break;
            }
            else
            {
                cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
            }
        }
    }
} // namespace sdds

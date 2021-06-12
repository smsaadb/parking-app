#ifndef PARKING
#define PARKING

#include <iostream>
#include <cstring>
#include "Car.h"
#include "Motorcycle.h"

using namespace std;

namespace sdds
{

    const int maxParkingSpots = 100;
    class Parking
    {
    private:
        Vehicle *parkingSpots[maxParkingSpots];
        int numOfSpots;
        int parkedVehicles;
        char *filename;
        Menu *mainMenu;
        Menu *vehicleMenu;

        bool isEmpty() const;
        void parkingStatus() const;
        void vehicleSelection();
        void returnVehicle();
        void listVehicles() const;
        bool closeParking();
        bool exitParking() const;
        bool loadDataFile();
        void saveDataFile() const;
        char yOrN() const;

    public:
        Parking(const char *name, int noOfSpots);
        Parking(const Parking &) = delete;
        Parking &operator=(const Parking &) = delete;
        ~Parking();
        int run();
    };
} // namespace sdds

#endif
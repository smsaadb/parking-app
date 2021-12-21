#include <fstream>
#include <iostream>
#include <ctype.h>
#include "Parking.h"
using namespace std;
using namespace sdds;
void runParking()
{
   Parking P("ParkingData.csv", 10);
   P.run();
}
void ShowDatafile()
{
   char ch;
   ifstream file("ParkingData.csv");
   cout << endl
        << "Content of ParkingData.csv after the program exits" << endl;
   cout << "-----------------------------------------------------------" << endl;
   while (file.get(ch))
   {
      cout << char(tolower(ch));
   }
   cout << "-----------------------------------------------------------" << endl;
}
int main()
{
   runParking();
   ShowDatafile();
   return 0;
}

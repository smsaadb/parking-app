cc=g++
flags=-Wall -std=c++11
files=Car.cpp Menu.cpp Motorcycle.cpp Parking.cpp ParkingAppTester.cpp ReadWritable.cpp Utils.cpp Vehicle.cpp

app: $(files)
	$(cc) $(flags) $^ -o $@



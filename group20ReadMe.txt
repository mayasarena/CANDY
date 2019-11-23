README CANDY group20

compile: g++ -Wall -pthread dispenser.cpp dispenser.hpp hopper.cpp hopper.hpp main.cpp -o project -lwiringPi -lpigpio -lrt

run: sudo ./project
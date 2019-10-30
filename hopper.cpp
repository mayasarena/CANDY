#include "hopper.h"

using namespace std;

int Hopper::getHopperID() {
    return Hopper::HopperID;
}

string Hopper::getCandyType() {
    return Hopper::candyType;
}

void Hopper::setCandyType(string input) {
    hopper::candyType = input;

}

int Hopper::getLastRefillTime() {
    return Hopper::lastRefillTime;

}

void Hopper::setLastRefillTime(int input) {
    Hopper::lastRefillTime = input;

}

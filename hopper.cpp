// Hello word!
// Hello word!
#include <string.h>
#include "hopper.h"

int hopperID;
string candyType;
int lastRefillTime;

int getHopperID() {
    return hopper::hopperID;
}

string getCandyType() {
    return hopper::candyType;
}

void setCandyType(string input) {
    hopper::candyType = input;

}

int getLastRefillTime() {
    return hopper::lastRefillTime;

}

void setLastRefillTime(int input) {
    hopper::lastRefillTime = input;

}

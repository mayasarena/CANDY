#include "hopper.h"

using namespace std;

int Hopper::getHopperID() {
    return this->hopper_id;
}

string Hopper::getCandyType() {
    return this->candy_type;
}

void Hopper::setCandyType(string input) {
    this->candyType = input;

}

int Hopper::getLastRefillTime() {
    return this->last_refill_time;

}

void Hopper::setLastRefillTime(int input) {
    this->last_refill_time = input;

}

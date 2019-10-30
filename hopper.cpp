#include "hopper.h"

using namespace std;

Hopper::Hopper(int hopper_id, string candy_name) {
    this->candy_type = candy_name;
    this->last_refill_time = 0;
    this->hopper_id = id;
}

~Hopper::Hopper() {
    
}

int Hopper::getHopperID() {
    return this->hopper_id;
}

string Hopper::getCandyType() {
    return this->candy_type;
}

int Hopper::getLastRefillTime() {
    return this->last_refill_time;

}

void Hopper::setCandyType(string input) {
    this->candyType = input;

}

void Hopper::setLastRefillTime(int input) {
    this->last_refill_time = input;

}

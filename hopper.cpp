//
//  hopper.cpp
//  CandyTesting
//
//  Created by Charlie Pieczonka on 2019-10-30.
//  Copyright © 2019 Team20. All rights reserved.
//

#include "hopper.hpp"

using namespace std;

Hopper::Hopper(string candy_name) {
    this->candy_type = candy_name;
    this->last_refill_time = 0;
    this->is_multi_hopper = false;
}

Hopper::Hopper(string candy_name, boolean isMultiHopper) {
    this->candy_type = candy_name;
    this->last_refill_time = 0;
    this->is_multi_hopper = true;
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

boolean Hopper::isMultiHopper() {
    return this->is_multi_hopper;
}

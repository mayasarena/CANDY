//
//  hopper.cpp
//  CandyTesting
//
//  Created by Charlie Pieczonka on 2019-10-30.
//  Copyright © 2019 Team20. All rights reserved.
//

#include "hopper.hpp"
#include <stdbool.h>

using namespace std;

Hopper::Hopper(string candy_name) {
    this->candy_type = candy_name;
    this->last_refill_time = 0;
    this->is_multi_hopper = false;
}

Hopper::Hopper(string candy_name, bool isMultiHopper) {
    this->candy_type = candy_name;
    this->last_refill_time = 0;
    this->is_multi_hopper = isMultiHopper;
}

Hopper::~Hopper() {
    
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
    this->candy_type = input;
}

void Hopper::setLastRefillTime(int input) {
    this->last_refill_time = input;
}

bool Hopper::isMultiHopper() {
    return this->is_multi_hopper;
}


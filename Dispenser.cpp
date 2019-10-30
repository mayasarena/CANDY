//
//  dispenser.cpp
//  CANDYTesting
//
//  Created by Charlie Pieczonka on 2019-10-28.
//  Copyright © 2019 Team20. All rights reserved.
//

#include "dispenser.hpp"

using namespace std;

/**
 Dispenser

 The constructor for the Dispenser class. Initializes all member values.
*/
Dispenser::Dispenser() {
    this->current_index = 0;
    this->size = 0;
}

// TODO: Might want a second constructor that accepts pre-initialized Hopper objects?
///**
// Dispenser
//
// The constructor for the Dispenser class. Initializes all member values.
//*/
//Dispenser::Dispenser() {
//    this->current_index = 0;
//    this->size = 0;
//}

Dispenser::~Dispenser() {
    // Might need to delete all Hopper objects?
}

/**
 currentIndex

 Selects the current candy hopper in the sequence.

 @return the id of the current candy hopper
*/
int Dispenser::getCurrentIndex() {
    return this->current_index;
}

/**
 getHopper

 Returns a pointer to the hopper at a given index.
 
 If the new index provided is out of range, the Dispenser will select
 the position at new_index modulus the number of hoppers in our system.

 @return a pointer to the Hopper at the given index (or current index)
 @throws an Out of Range exception if there are no hoppers to select
*/
Hopper* Dispenser::getHopper(int index) {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    return this->hoppers[index % this->size];
}

/**
 getHopper

 Returns a pointer to the hopper at the current index.

 @return a pointer to the Hopper at the given index (or current index)
 @throws an Out of Range exception if there are no hoppers to select
*/
Hopper* Dispenser::getHopper() {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    return this->getHopper(this->current_index);
}

/**
 setCurrentIndex

 Setter method for the current candy hopper index.
 If the new index provided is out of range, the Dispenser will select
 the position at new_index modulus the number of hoppers in our system.

 @return the id of the new candy hopper
 @throws an Out of Range exception if there are no hoppers to select
*/
int Dispenser::setCurrentIndex(int new_index) {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    this->current_index = new_index % this->size;
    return this->current_index;
}

/**
 nextIndex

 Selects the next candy hopper in the sequence.

 @return the id of the next candy hopper
 @throws an Out of Range exception if there are no hoppers to select
*/
int Dispenser::nextIndex() {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    this->current_index = (this->current_index + 1) % this->size;
    
    return this->current_index;
}

/**
 dispense

 Dispenses the candy at the current index.

 @throws an Out of Range exception if there are no hoppers to select
*/
void Dispenser::dispense() {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    // TODO: Code to dispense
}

/**
 addHopper

 Appends a pointer to a Hopper object at the end of the hoppers vector.
 
 @returns the index of the new hopper pointer
 @throws an Out of Range exception if there are no hoppers to select
*/
int Dispenser::addHopper(Hopper* new_hopper) {
    return this->addHopper(new_hopper, this->size);
}

/**
 addHopper

 Adds a pointer to a Hopper in the hoppers vector.
 If an index is provided, the new hopper will be added to the position at new_index modulus the number of hoppers in our system. Otherwise, the new hopper is appended to the end.
 
 @returns the index of the new hopper pointer
 @throws an Out of Range exception if there are no hoppers to select
*/
int Dispenser::addHopper(Hopper* new_hopper, int index) {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    if (index == this->size) {
        hoppers.push_back(new_hopper);
        this->size++;
    } else {
        this->size++;
        int insert_index = index % this->size;
        hoppers.insert(hoppers.begin() + insert_index, new_hopper);
    }
    return index % this->size;
}

/**
 removeHopper

 Removes the hopper at a given index in the hopper vector.
 The hopper at the position at new_index modulus the number of hoppers in our system will be removed.
 
 @returns the index of the new hopper pointer
 @throws an Out of Range exception if there are no hoppers to select
*/
void Dispenser::removeHopper(int index) {
    this->hoppers.erase(this->hoppers.begin() + (index % this->size));
}

/**
 removeHopper

 Removes a given pointer in the hoppers vector.
 
 @returns the index of the new hopper pointer
 @throws an Invalid Argument exception if the Hopper does not exist
*/
void Dispenser::removeHopper(Hopper* hopper) {
    vector<Hopper*>::iterator it = std::find(this->hoppers.begin(), this->hoppers.end(), hopper);
    int position = distance(this->hoppers.begin(), it);
    this->removeHopper(position);
}

int main(int argc, const char * argv[]) {
    return 0;
}

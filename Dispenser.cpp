//
//  dispenser.cpp
//  CandyTesting
//
//  Created by Charlie Pieczonka on 2019-10-30.
//  Copyright © 2019 Team20. All rights reserved.
//

#include "hopper.hpp"
#include "dispenser.hpp"
using namespace std;

/**
 * Dispenser
 * @brief The constructor for the Dispenser class. Initializes all member values.
 The constructor for the Dispenser class. Initializes all member values.
 */
Dispenser::Dispenser() {
    this->current_index = 0;
    this->size = 0;
    gpioInitialise();
    
}

typedef struct {
    int gpio;
    int minPulse;
    int maxPulse;
    int pw;
    int pwInc;
    int connected;
} servoInf_t;

servoInf_t servoInf[]=
{
    { 0, 1000, 2000, 1500,   2, 0}, /* change 0 to 1 to enable servo */
    { 1, 1000, 2000, 1500,  -2, 0},
    { 2, 1000, 2000, 1500,   3, 0},
    { 3, 1000, 2000, 1500,  -3, 0},
    { 4, 1000, 2000, 1500,   5, 0},
    { 5, 1000, 2000, 1500,  -5, 0},
    { 6, 1000, 2000, 1500,   7, 0},
    { 7, 1000, 2000, 1500,  -7, 0},
    
    { 8, 1000, 2000, 1500,  11, 0},
    { 9, 1000, 2000, 1500, -11, 0},
    {10, 1000, 2000, 1500,  13, 0},
    {11, 1000, 2000, 1500, -13, 0},
    {12, 1000, 2000, 1500,  17, 1},
    {13, 1000, 2000, 1500, -17, 0},
    {14, 1000, 2000, 1500,  19, 0},
    {15, 1000, 2000, 1500, -19, 0},
    
    {16, 1000, 2000, 1500,  23, 0},
    {17, 1000, 2000, 1500, -23, 0},
    {18, 1000, 2000, 1500,  29, 0},
    {19, 1000, 2000, 1500, -29, 1},
    {20, 1000, 2000, 1500,  31, 0},
    {21, 1000, 2000, 1500, -31, 1},
    {22, 1000, 2000, 1500,  37, 0},
    {23, 1000, 2000, 1500, -37, 1},
    
    {24, 1000, 2000, 1500,  41, 0},
    {25, 1000, 2000, 1500, -41, 0},
    {26, 1000, 2000, 1500,  43, 0},
    {27, 1000, 2000, 1500, -43, 0},
    {28, 1000, 2000, 1500,  47, 0},
    {29, 1000, 2000, 1500, -47, 0},
    {30, 1000, 2000, 1500,  53, 0},
    {31, 1000, 2000, 1500, -53, 0},
};

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
 * getSize
 Returns the number of hoppers
 @return the number of hoppers
 */
int Dispenser::getSize() {
    return this->size;
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
 openDispenser
 
 Dispenses the candy at the current index.
 
 @throws an Out of Range exception if there are no hoppers to select
 */
void Dispenser::openDispenser() {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    
    std::cout << "OpenDispenser() has been reached\n";
    
    // TODO: fix softServo errors
    if (current_index == 0){
        std::cout << "open index 0\n";
        servoInf[23].pw -= 940;
        gpioServo(servoInf[23].gpio, servoInf[23].pw);
    }
    
    if (current_index == 1){
        std::cout << "open index 1\n";
        servoInf[12].pw -= 960;
        gpioServo(servoInf[12].gpio, servoInf[12].pw);
    }
    
    if (current_index == 2){
        std::cout << "open index 0\n";
        servoInf[21].pw -= 940;
        gpioServo(servoInf[21].gpio, servoInf[21].pw);
    }
    
    if (current_index == 3){
        std::cout << "open index 0\n";
        servoInf[19].pw -= 940;
        gpioServo(servoInf[19].gpio, servoInf[19].pw);
    }
    
    if (current_index == 4){
        std::cout << "open index 4\n";
        servoInf[23].pw -= 300;
        gpioServo(servoInf[23].gpio, servoInf[23].pw);
        servoInf[12].pw -= 300;
        gpioServo(servoInf[12].gpio, servoInf[12].pw);
        servoInf[21].pw -= 940;
        gpioServo(servoInf[21].gpio, servoInf[21].pw);
        servoInf[19].pw -= 940;
        gpioServo(servoInf[19].gpio, servoInf[19].pw);
    }
}

/**
 closeDispenser
 
 Dispenses the candy at the current index.
 
 @throws an Out of Range exception if there are no hoppers to select
 */
void Dispenser::closeDispenser() {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    
    std::cout << "CloseDispenser() has been reached\n";
    
    // TODO: fix softServo errors
    if (current_index == 0){
        std::cout << "close index 0\n";
        servoInf[23].pw += 940;
        gpioServo(servoInf[23].gpio, servoInf[23].pw);
    }
    
    if (current_index == 1){
        std::cout << "close index 1\n";
        servoInf[12].pw += 960;
        gpioServo(servoInf[12].gpio, servoInf[12].pw);
    }
    
    if (current_index == 2){
        std::cout << "open index 0\n";
        servoInf[21].pw += 940;
        gpioServo(servoInf[21].gpio, servoInf[21].pw);
    }
    
    if (current_index == 3){
        std::cout << "open index 0\n";
        servoInf[19].pw += 940;
        gpioServo(servoInf[19].gpio, servoInf[19].pw);
    }
    
    if (current_index == 4){
        std::cout << "open index 4\n";
        servoInf[23].pw += 300;
        gpioServo(servoInf[23].gpio, servoInf[23].pw);
        servoInf[12].pw += 300;
        gpioServo(servoInf[12].gpio, servoInf[12].pw);
        servoInf[21].pw += 940;
        gpioServo(servoInf[21].gpio, servoInf[21].pw);
        servoInf[19].pw += 940;
        gpioServo(servoInf[19].gpio, servoInf[19].pw);
    }
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

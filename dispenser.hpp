/**
 * @file hopper.cpp
 * @author Charlie, Marissa, Maya, Fletcher, and Julie
 * @date 28 Nov 2019
 * @brief Header file for dispenser class
 *
 */

#ifndef dispenser_hpp
#define dispenser_hpp

#include "hopper.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <wiringPi.h>
#include <pigpio.h>

class Dispenser {
public:
    Dispenser();
    Dispenser(std::vector<Hopper*> hoppers);
    ~Dispenser();
    int getCurrentIndex();
    Hopper* getHopper(int index);
    Hopper* getHopper();
    int getSize();
    int setCurrentIndex(int new_index);
    int nextIndex();
    void openDispenser();
    void closeDispenser();
    int addHopper(Hopper* new_hopper);
    int addHopper(Hopper* new_hopper, int index);
    void removeHopper(int index);
    void removeHopper(Hopper* new_hopper);
    
private:
    int current_index; ///< integer index number
    std::vector<Hopper*> hoppers; ///< Vector of pointers to Hopper objects
    int size; ///< number of hoppers in the dispenser
};

#endif /* dispenser_hpp */


//
//  dispenser.hpp
//  CandyTesting
//
//  Created by Charlie Pieczonka on 2019-10-30.
//  Copyright © 2019 Team20. All rights reserved.
//

#ifndef dispenser_hpp
#define dispenser_hpp

#include "hopper.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>

class Dispenser {
public:
    Dispenser();
    Dispenser(std::vector<Hopper*> hoppers);
    ~Dispenser();
    int getCurrentIndex();
    Hopper* getHopper(int index);
    Hopper* getHopper();
    int setCurrentIndex(int new_index);
    int nextIndex();
    void openDispenser();
    void closeDispenser();
    int addHopper(Hopper* new_hopper);
    int addHopper(Hopper* new_hopper, int index);
    void removeHopper(int index);
    void removeHopper(Hopper* new_hopper);
    
private:
    int current_index;
    std::vector<Hopper*> hoppers;       // Vector of pointers to Hopper objects
    int size;
    // missing some sort of internal clock - if we plan on implementing an expiration time
};

#endif /* dispenser_hpp */

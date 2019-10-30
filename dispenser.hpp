//
//  Dispensing.hpp
//  CANDYTesting
//
//  Created by Charlie Pieczonka on 2019-10-28.
//  Copyright © 2019 Team20. All rights reserved.
//

#ifndef dispenser_h
#define dispenser_h

#include "hopper.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>

class Dispenser {
    public:
        Dispenser();
        Dispenser(std::vector<Hopper::Hopper*> hoppers);
        ~Dispenser();
        int getCurrentIndex();
        Hopper::Hopper* getHopper(int index = this->current_index);
        int setCurrentIndex(int new_index);
        int nextIndex();
        int dispense(int hopper_id);
        int addHopper(Hopper::Hopper* new_hopper, int index = this->size);
        void removeHopper(int index);
        void removeHopper(Hopper::Hopper* new_hopper);
    
    private:
        int current_index;
        std::vector<Hopper::Hopper*> hoppers;       // Vector of pointers to Hopper objects
        int size;
        // missing some sort of internal clock - if we plan on implementing an expiration time
}

#endif /* Dispenser_h */

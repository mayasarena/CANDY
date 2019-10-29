//
//  Dispensing.hpp
//  CANDYTesting
//
//  Created by Charlie Pieczonka on 2019-10-28.
//  Copyright © 2019 Team20. All rights reserved.
//

#ifndef Dispensing_h
#define Dispensing_h

#include "hopper.hpp"
#include <stdio.h>
#include <vector>

class Dispenser {

    private:
        int current_index;
        std::vector<hopper> hoppers;

    public:
        Dispenser();
        ~Dispenser();
        void dispense(int hopper_id);
        void nextIndex(int current_index);
        int getCurrentIndex();
        void setCurrentIndex(int new_index);
        hopper getHopper(int current_index);
}

#endif /* Dispensing_h */

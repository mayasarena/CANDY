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

class dispenser {
    
    private:
        int currentIndex;
        std::vector<hopper> hoppers;
    
    public:
        dispenser();
        ~dispenser();
        void dispense(int hopperID);
        void nextIndex(int currentIndex);
        int getCurrentIndex();
        void setCurrentIndex();
        hopper getHopper(int currentIndex);
}

#endif /* Dispensing_h */

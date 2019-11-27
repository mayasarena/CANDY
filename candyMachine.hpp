//
//  candyMachine.hpp
//  CandyTesting
//
//  Created by Charlie Pieczonka on 2019-10-30.
//  Copyright © 2019 Team20. All rights reserved.
//

#ifndef candyMachine_hpp
#define candyMachine_hpp

#include "dispenser.hpp"
#include "servos.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <wiringPi.h>
#include <softServo.h>
#include <softPwm.h>
#include <pigpio.h>

class CandyMachine {
public:
    CandyMachine();
    // CandyMachine(std::vector<Hopper*> hoppers);
    ~CandyMachine();
    void runMachine();
    void buildDispenser();
    void selectNext();
    void openDispenser();
    void closeDispenser();

private:
    Dispenser* dispenser;       // Vector of pointers to Hopper objects
    Button indexButton;
    Button dispenseButton;
};

#endif /* candyMachine_hpp */

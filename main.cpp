//
//  main.cpp
//  CandyTesting
//
//  Created by Charlie Pieczonka on 2019-10-30.
//  Copyright © 2019 Team20. All rights reserved.
//

#include <iostream>
#include "wiringPi.h"
#include "dispenser.hpp"
#include "hopper.hpp" // "" to suppress errors, <> needed when actually testing

void pinSetup(){
    
    // 1 output set up for each LED
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    
    // 1 output set up for each servo
    //
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    
    // 1 input set up for each button
    pinMode(9, INPUT); // index button
    pinMode(10, INPUT); // dispense button
}

void buildDispenser(Dispenser * disp) {
    Hopper skittles_hopper = Hopper("Skittles");
    Hopper mm_hopper = Hopper("M&M");
    Hopper candy_corn_hopper = Hopper("Candy Corn");
    disp->addHopper(&skittles_hopper);
    disp->addHopper(&mm_hopper);
    disp->addHopper(&candy_corn_hopper);
}

int main(int argc, const char * argv[]) {
    
    wiringPiSetup();
    pinSetup();
    
    Dispenser CANDY;
    buildDispenser(&CANDY);
    
    
    
    // main program loop
    while(true){
        
        // if index button is pressed: JIRA TASK #
        if(digitalRead(9) == true){
            
            // our current index matches the pin number for each LED
            // so to turn off the current light, digital write false to the current index
            digitalWrite(CANDY.getCurrentIndex(), false);
            
            // set current index to next
            CANDY.nextIndex();
            
            // turn on the now currently selected LED
            digitalWrite(CANDY.getCurrentIndex(), true);
        }
        
        // if dispense button is pressed: JIRA TASK #
        if(digitalRead(10) == true){
            //TODO: power the correct servo to dispense based on hopper vector
            
            CANDY.openDispenser(); // open hopper a specific amount
            while(digitalRead(10) == true){} // wait until dispense button is not pressed
            CANDY.closeDispenser(); // close hopper
        }
    }
}

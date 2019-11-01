//
//  main.cpp
//  CandyTesting
//
//  Created by Charlie PDog on 2019-10-30.
//  Copyright © 2019 Team20. All rights reserved.
//

#include <iostream>
#include <wiringPi.h>
#include <softServo.h>
#include "dispenser.hpp"
#include "hopper.hpp"

void pinSetup() {
    // 1 output set up for each LED
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    
    // TODO: determine cause of error when initializing with softServo
    //set up pins 5 through 8 as servos
    //softServoSetup(5, 6, 7, 8, 5, 6, 7, 8);
    
    // 1 input set up for each button
    pinMode(9, INPUT); // index button
    pinMode(10, INPUT); // dispense button
}

void selectNextHopper(Dispenser * disp) {
    // Our current index matches the pin number for each LED
    // so to turn off the current light, digital write false to the current index
    digitalWrite(disp->getCurrentIndex(), false);
    
    // Set current index to next
    disp->nextIndex();
    
    // Turn on the now currently selected LED
    digitalWrite(disp->getCurrentIndex(), true);
}

void buildDispenser(Dispenser * disp) {
    // Initialize candy hoppers.
    Hopper skittles_hopper = Hopper("Skittles");
    Hopper mm_hopper = Hopper("M&M");
    Hopper candy_corn_hopper = Hopper("Candy Corn");
    
    // Add candy hoppers to dispenser.
    disp->addHopper(&skittles_hopper);
    disp->addHopper(&mm_hopper);
    disp->addHopper(&candy_corn_hopper);
    for (int i = 0; i < disp->getSize(); i++) {
        std::cout << "Current candy selected (light will specify): ";
        std::cout << disp->getHopper()->getCandyType()<< "\n";
        
        // We know the button isn't actually hooked up, but this simulates the indexing/candy selection task in Jira.
        std::cout << "THE BUTTON IS PRESSED, INDEXING TO THE NEXT CANDY\n\n";
        selectNextHopper(disp);
    }
}

int main(int argc, const char * argv[]) {
    
    wiringPiSetup();
    pinSetup();
    
    Dispenser CANDY;
    buildDispenser(&CANDY);
    
    // Main program loop
    while(true){
        
        // If the next Hopper button is pressed: JIRA TASK
        if(digitalRead(9)){
            selectNextHopper(&CANDY);
        }
        
        // If dispense button is pressed: JIRA TASK
        if(digitalRead(10)){
            //TODO: power the correct servo to dispense based on hopper vector
            
            // JIRA TASK: DISPENSE BUTTON PRESSED.
            std::cout << "JIRA TASK: DISPENSE BUTTON PRESSED. NOW DISPENSING CANDY\n";
            
            CANDY.openDispenser(); // Open hopper a specific amount
            while(digitalRead(10)) {
                // Wait until dispense button is not pressed
                // NOTE: Once our hardware is properly set up, we'll run this while loop until the dispense button has been lifted.
                // For now, we'll simulate a button press and terminate from the loop after one iteration.
                break;
            }
            
            std::cout << "JIRA TASK: DISPENSE BUTTON LIFTED. DISPENSER CLOSED\n";
            CANDY.closeDispenser(); // Close hopper once button has been lifted
            
            // NOTE: Once our hardware is properly set up, we'll run this while loop until the dispense button has been lifted.
            // For now, we have simulated a single dispense process and terminate from the loop after one iteration.
            std::cout << "Thank you for coming! Enjoy your CANDY!\n";
            return 0;
        }
    }
}


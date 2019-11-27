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
#include <softPwm.h>
#include "dispenser.hpp"
#include "hopper.hpp"
#include <pigpio.h>

/* forward prototype */
void pinSetup() {
    // 1 output set up for each LED
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);

    // multicoloured light
    pinMode(21, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);

    // 1 input set up for each button
    pinMode(5, INPUT); // dispense button
    pinMode(6, INPUT); // index button

}

void selectNextHopper(Dispenser * disp) {
    // Our current index matches the pin number for each LED
    // so to turn off the current light, digital write false to the current index

    if (disp->getCurrentIndex() != 4){
        digitalWrite(disp->getCurrentIndex(), false);
    }
    else{
        digitalWrite(21, false);
        digitalWrite(22, false);
        digitalWrite(23, false);
    }

    // Set current index to next
    disp->nextIndex();

    // Turn on the now currently selected LED if not multicoloured
    if (disp->getCurrentIndex() != 4){
        digitalWrite(disp->getCurrentIndex(), true);
    }
    else{
        digitalWrite(21, true);
    }

}

void buildDispenser(Dispenser * disp) {
    // Initialize candy hoppers.
    Hopper skittles_hopper = Hopper("Skittles");
    Hopper mm_hopper = Hopper("M&M");
    Hopper candy_corn_hopper = Hopper("Candy Corn");
    Hopper gum_ball_hopper = Hopper("Gum Ball");
    Hopper all_hopper = Hopper("All");

    // Add candy hoppers to dispenser.
    disp->addHopper(&skittles_hopper);
    disp->addHopper(&mm_hopper);
    disp->addHopper(&candy_corn_hopper);
    disp->addHopper(&gum_ball_hopper);
    disp->addHopper(&all_hopper);
    for (int i = 0; i < disp->getSize(); i++) {
        std::cout << "Current candy selected (light will specify): ";
        std::cout << disp->getHopper()->getCandyType()<< "\n";

        // We know the button isn't actually hooked up, but this simulates the indexing/candy selection task in Jira.
        std::cout << "THE BUTTON IS PRESSED, INDEXING TO THE NEXT CANDY\n\n";
        selectNextHopper(disp);
    }
}


int main(int argc, const char * argv[]) {

    if (gpioInitialise() < 0) return 1;
    if (wiringPiSetup() < 0) return 1;
    pinSetup();
    int MultiCount = 1;
    int pinNum = 21;

    Dispenser CANDY;
    buildDispenser(&CANDY);

    // Main program loop
    while(true) {

        if (CANDY.getCurrentIndex() == 4) {
            digitalWrite(pinNum, false);
            pinNum = (MultiCount%3)+21;
            digitalWrite(pinNum, true);
            MultiCount++;
            delay(100);
        }

        // If the next Hopper button is pressed: JIRA TASK
        if (!digitalRead(6)) {
            selectNextHopper(&CANDY);
            // A cooldown period for our button press listener
            delay(200);
        }

        // If dispense button is pressed: JIRA TASK
        if (!digitalRead(5)) {

            // JIRA TASK: DISPENSE BUTTON PRESSED.
            std::cout << "JIRA TASK: DISPENSE BUTTON PRESSED. NOW DISPENSING CANDY\n";

            CANDY.openDispenser();

            // Wait until dispense button is not pressed
            while (!digitalRead(5)) {

            }

            std::cout << "JIRA TASK: DISPENSE BUTTON LIFTED. DISPENSER CLOSED\n";
            CANDY.closeDispenser(); // Close hopper once button has been lifted

            std::cout << "Thank you for coming! Enjoy your CANDY!\n";
        }
    }
    return 0;
}

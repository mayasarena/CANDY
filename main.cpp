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

/*
 typedef struct
 {
 int gpio;
 int minPulse;
 int maxPulse;
 int pw;
 int pwInc;
 int connected;
 } servoInf_t;
 
 
 servoInf_t servoInf[]=
 {
 { 0, 1000, 2000, 1500,   2, 0}, // change 0 to 1 to enable servo
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
 {19, 1000, 2000, 1500, -29, 0},
 {20, 1000, 2000, 1500,  31, 0},
 {21, 1000, 2000, 1500, -31, 0},
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
 
 */
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
/*
 void servoTick(void * userdata)
 {
 int s;
 
 for (s=0; s<sizeof(servoInf)/sizeof(servoInf_t); s++)
 {
 if (servoInf[s].connected) // are we using this servo?
 {
 //move servo by its increment
 servoInf[s].pw += servoInf[s].pwInc;
 
 // bounce back from ends
 if ((servoInf[s].pw < servoInf[s].minPulse) ||
 (servoInf[s].pw > servoInf[s].maxPulse))
 {
 servoInf[s].pwInc = - servoInf[s].pwInc;
 
 servoInf[s].pw += (2 * servoInf[s].pwInc);
 }
 
 // position servo
 gpioServo(servoInf[s].gpio, servoInf[s].pw);
 }
 }
 }
 */

int main(int argc, const char * argv[]) {
    
    if (gpioInitialise()<0) return 1;
    if (wiringPiSetup()<0) return 1;
    pinSetup();
    int MultiCount = 1;
    int pinNum = 21;
    
    //gpioServo(servoInf[23].gpio, -200);
    
    Dispenser CANDY;
    buildDispenser(&CANDY);
    
    // Main program loop
    while(true){
        
        if (CANDY.getCurrentIndex() == 4){
            //std::cout << "pin num off = " << pinNum << "\n";
            digitalWrite(pinNum, false);
            pinNum = (MultiCount%3)+21;
            //std::cout << "pin num on = " << pinNum << "\n";
            digitalWrite(pinNum, true);
            MultiCount++;
            //std::cout << "multiDelay\n";
            delay(100);
        }
        
        // If the next Hopper button is pressed: JIRA TASK
        if(!digitalRead(6)){
            selectNextHopper(&CANDY);
            delay(200);
        }
        
        // If dispense button is pressed: JIRA TASK
        if(!digitalRead(5)){
            //TODO: power the correct servo to dispense based on hopper vector
            
            // JIRA TASK: DISPENSE BUTTON PRESSED.
            std::cout << "JIRA TASK: DISPENSE BUTTON PRESSED. NOW DISPENSING CANDY\n";
            
            CANDY.openDispenser(); // Open hopper a specifif (gpioInitialise()<0) return 1;c amount
            
            
            //*********** Temporary servo movement OPEN ****************
            /*
             if (CANDY.getCurrentIndex() == 0){
             std::cout << "open index 0\n";
             servoInf[23].pw -= 940;
             gpioServo(servoInf[23].gpio, servoInf[23].pw);
             }
             
             if (CANDY.getCurrentIndex() == 1){
             std::cout << "open index 1\n";
             servoInf[12].pw -= 960;
             gpioServo(servoInf[12].gpio, servoInf[12].pw);
             }
             
             if (CANDY.getCurrentIndex() == 4){
             std::cout << "open index 4\n";
             servoInf[23].pw -= 300;
             gpioServo(servoInf[23].gpio, servoInf[23].pw);
             servoInf[12].pw -= 300;
             gpioServo(servoInf[12].gpio, servoInf[12].pw);
             }
             */
            // *********************************************************
            
            
            while(!digitalRead(5)) {
                // Wait until dispense button is not pressed
                // NOTE: Once our hardware is properly set up, we'll run this while loop until the dispense button has been lifted.
                // For now, we'll simulate a button press and terminate from the loop after one iteration.
                //std::cout << "DISPENSING\n";
                //break;
            }
            
            std::cout << "JIRA TASK: DISPENSE BUTTON LIFTED. DISPENSER CLOSED\n";
            CANDY.closeDispenser(); // Close hopper once button has been lifted
            
            //*********** Temporary servo movement CLOSE ****************
            /*
             if (CANDY.getCurrentIndex() == 0){
             std::cout << "close index 0\n";
             servoInf[23].pw += 940;
             gpioServo(servoInf[23].gpio, servoInf[23].pw);
             }
             
             if (CANDY.getCurrentIndex() == 1){
             std::cout << "close index 1\n";
             servoInf[12].pw += 960;
             gpioServo(servoInf[12].gpio, servoInf[12].pw);
             }
             
             if (CANDY.getCurrentIndex() == 4){
             std::cout << "open index 4\n";
             servoInf[23].pw += 300;
             gpioServo(servoInf[23].gpio, servoInf[23].pw);
             servoInf[12].pw += 300;
             gpioServo(servoInf[12].gpio, servoInf[12].pw);
             }
             */
            // ***
            
            // NOTE: Once our hardware is properly set up, we'll run this while loop until the dispense button has been lifted.
            // For now, we have simulated a single dispense process and terminate from the loop after one iteration.
            std::cout << "Thank you for coming! Enjoy your CANDY!\n";
        }
        
        //gpioSetTimerFuncEx(0, 100, servoTick, 0);
        
    }
    return 0;
}


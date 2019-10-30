//
//  main.cpp
//  CandyTesting
//
//  Created by Charlie Pieczonka on 2019-10-30.
//  Copyright © 2019 Team20. All rights reserved.
//

#include <iostream>
#include <wiringPi.h>

int main(int argc, const char * argv[]) {
<<<<<<< HEAD

    wiringPiSetup();
    
    // 1 output set up for each LED
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    
    // 1 output set up for each servo
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    
    // 1 input set up for each button
    pinMode(9, INPUT); // index button
    pinMode(10, INPUT); // dispense button
    
    // main program loop
    while(true)
    {
        // if index button is pressed
        if(digitalRead(9) == true)
        {
            //TODO: index hopper based on hopper vector, light the correct LED
        }
        
        // if dispense button is pressed
        if(digitalRead(10) == true)
        {
            //TODO: power the correct servo to dispense based on hopper vector
        }
    }
=======
    // insert code here...
    std::cout << "Hello, World!!\n";
>>>>>>> 87dcbde0dc48b84309970003d0952a7b2332b0ed
    return 0;
}

/**
 * @file main.cpp
 * @author Charlie, Marissa, Maya, Fletcher, and Julie
 * @date 27 Nov 2019
 * @brief File containing the main function for the entire program.
 *
 */

#include <iostream>
#include <wiringPi.h>
#include <softServo.h>
#include <softPwm.h>
#include "dispenser.hpp"
#include "hopper.hpp"
#include <pigpio.h>

/**
 * @brief A function to set up the Raspberry Pi GPIO pins
 * Set up the each GPIO pin used for the Candy LED lights as OUTPUT and each
 * button as INPUT.
 * @return NULL is always returned.
 */
void pinSetup() {
    // Set up output pins for LED lights
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);

    // Set up GPIO pin for multi-coloured LED light
    pinMode(21, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);

    // Set up input pins for the Dispense and Index/Next Candy button
    pinMode(5, INPUT);  // Dispense button
    pinMode(6, INPUT);  // Index AKA "Next Candy" button

}

/**
 * @brief A function to select the next candy in the Candy Machine
 * Selects the next candy in the machine, turning off the light of the
 * previously-selected candy and turning on the light of the newly-selected
 * candy.
 * @param disp    A pointer to the Dispenser object, containing the hoppers
 * @return NULL is always returned.
 */
void selectNextHopper(Dispenser * disp) {
    // To select the next hopper, we first turn off the current light by digital
    // writing the pin assigned to the candy to false.
    if (disp->getCurrentIndex() != disp->getSize() - 1){
        digitalWrite(disp->getCurrentIndex(), false);
    } else {
        // Write to all 3 GPIO pins for the multi-coloured candy
        digitalWrite(21, false);
        digitalWrite(22, false);
        digitalWrite(23, false);
    }

    // Iterate to the next hopper index in the dispenser
    disp->nextIndex();

    // Turn on the newly-selected LED light if not multicoloured
    if (disp->getCurrentIndex() != disp->getSize() - 1) {
        digitalWrite(disp->getCurrentIndex(), true);
    } else {
        // Write to the first GPIO pin for the multi-coloured candy
        digitalWrite(21, true);
    }

}

/**
 * @brief A function to build the Dispenser object with all default candy options.
 * Initializes all the default candy Hoppers (Skittles, M&Ms, Reese's Pieces,
 * and Fruit Blasters) and adds them to the Dispenser object
 * @param disp    A pointer to the Dispenser object, containing the hoppers
 * @return NULL is always returned.
 */
void buildDispenser(Dispenser * disp) {
    // Initialize default candy hoppers
    Hopper skittles_hopper = Hopper("Skittles", false);
    Hopper mm_hopper = Hopper("M&M", false);
    Hopper candy_corn_hopper = Hopper("Reese's Pieces", false);
    Hopper gum_ball_hopper = Hopper("Fruit Blasters", false);
    Hopper all_hopper = Hopper("All", true);

    // Add default candy hoppers to dispenser.
    disp->addHopper(&skittles_hopper);
    disp->addHopper(&mm_hopper);
    disp->addHopper(&candy_corn_hopper);
    disp->addHopper(&gum_ball_hopper);
    disp->addHopper(&all_hopper);
}

/**
 * @brief The main function of the program
 * Initializes and builds the Dispenser object, then controls all the button
 * and LED light indexing, as well as the servo motor.
 * @return 1 if the GPIO and WiringPi setup completed unsuccessfully. Otherwise,
 * 0 is returned.
 */
int main(int argc, const char * argv[]) {
    // Initialize the Raspberry Pi's GPIO and wiringPi library
    if (gpioInitialise() < 0) return 1;
    if (wiringPiSetup() < 0) return 1;

    pinSetup();           // Set up all pin numbers for buttons and LED lights.

    // Counter used to change the colour of the multi-colour light
    int multi_count = 1;
    // Default starting pin number for the multi-colour light
    int pin_num = 21;

    Dispenser CANDY;
    buildDispenser(&CANDY);

    // Main program loop
    while (true) {
        // If current index points to the multi-coloured light
        if (CANDY.getCurrentIndex() == disp->getSize() - 1) {
            digitalWrite(pin_num, false);
            // Change the colour of the multi-colour light
            pin_num = (multi_count % 3) + 21;
            digitalWrite(pin_num, true);
            multi_count++;
            delay(100);     // A cooldown period for our button press listener
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

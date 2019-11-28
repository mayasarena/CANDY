/**
 * @file Dispenser.cpp
 * @author Charles Pieczonka, Marissa Liu, Fletcher Smith, Maya Murad, Julie Winer
 * @date 28 Nov 2019
 * @brief Implementation of our dispenser class
 *
 * This dispenser implementation contains methods that add and remove
 * individual hoppers to the dispenser, as well as methods that index
 * the current hopper and open and close the correct hoppers
 */

#include "hopper.hpp"
#include "dispenser.hpp"
#include "wiringPi.h"
#include "softServo.h"
using namespace std;

/**
 * @brief Dispenser constructor
 *
 * Initializes an instance of the dispenser class and starts
 * the current index begins at zero as well as the size (amount of hoppers)
 */
Dispenser::Dispenser() {
    this->current_index = 0;
    this->size = 0;
    gpioInitialise();
}

typedef struct {
    int gpio;
    int minPulse;
    int maxPulse;
    int pw;
    int pwInc;
    int connected;
} servoInf_t;

servoInf_t servoInf[]=
{
    { 0, 1000, 2000, 1500,   2, 0}, /* change 0 to 1 to enable servo */
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
    {19, 1000, 2000, 1500, -29, 1},
    {20, 1000, 2000, 1500,  31, 0},
    {21, 1000, 2000, 1500, -31, 1},
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

/**
 * @brief Dispenser destructor
 *
 * Any memory that needs to be freed will be done here
 */
Dispenser::~Dispenser() {
}

/**
 * @brief Gets the current candy hopper in the sequence.
 *
 * The current index is used for a variety of reasons, including
 * to determine what servo motor to activate when dispensing.
 * Since the current_index variable is private a getter is needed.
 *
 * @returns The id of the current candy hopper
 */
int Dispenser::getCurrentIndex() {
    return this->current_index;
}

/**
 * @brief Gets the size of the dispenser
 *
 * The size of the dispenser refers to the amount of hoppers associated
 * with the dispenser class. Since size is a private variable, a getter is needed.
 *
 * @returns The number of hoppers in the specified Dispenser
 */
int Dispenser::getSize() {
    return this->size;
}

/**
 * @brief Gets an instance of the hopper class at the specified index
 *
 * If the new index provided is out of range, the Dispenser will select
 * the position at new_index modulus the number of hoppers in our system.
 *
 * @param index The index of the hopper to be retrieved
 * @returns A pointer to the hopper at the given index
 * @throws An Out of Range exception if there are no hoppers to select
 */
Hopper* Dispenser::getHopper(int index) {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    return this->hoppers[index % this->size];
}

/**
 * @brief Gets an instance of the hopper class at the current index
 *
 * An overload of the getHopper method that returns the hopper at the current index
 * if no index is specified as a parameter
 *
 * @returns A pointer to the hopper at the current index
 * @throws An Out of Range exception if there are no hoppers to select
 */
Hopper* Dispenser::getHopper() {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    return this->getHopper(this->current_index);
}

/**
 * @brief Changes the index of the current candy hopper
 *
 * If the new index provided is out of range, the Dispenser will select
 * the position at new_index modulus the number of hoppers in our system.
 *
 * @param new_index The index value to be assigned to the hopper
 * @return The id of the new candy hopper
 * @throws An Out of Range exception if there are no hoppers to select
 */
int Dispenser::setCurrentIndex(int new_index) {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    this->current_index = new_index % this->size;
    return this->current_index;
}

/**
 * @brief Selects the next candy hopper in the sequence.
 *
 * This method is used to index which hopper is selected
 * and this change the LED that is lit, as well as the servo that will
 * be activated upon dispensing. The method simply changes the current index
 * to the next hopper in line.
 *
 * @returns The id of the next candy hopper
 * @throws An Out of Range exception if there are no hoppers to select
 */
int Dispenser::nextIndex() {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    this->current_index = (this->current_index + 1) % this->size;
    
    return this->current_index;
}

/**
 * @brief Open the hopper at the current index
 *
 * This method utilizes current index to power the associated servo motor
 * Thus opening the hopper and dispensing the candy. If the current index is
 * on the multicoloured LED, all hoppers are opened.
 *
 * @throws An Out of Range exception if there are no hoppers to select
 */
void Dispenser::openDispenser() {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    
    std::cout << "OpenDispenser() has been reached\n";
    
    if (current_index == 0){
        std::cout << "open index 0\n";
        servoInf[23].pw -= 940;
        gpioServo(servoInf[23].gpio, servoInf[23].pw);
    }
    
    if (current_index == 1){
        std::cout << "open index 1\n";
        servoInf[12].pw -= 960;
        gpioServo(servoInf[12].gpio, servoInf[12].pw);
    }
    
    if (current_index == 2){
        std::cout << "open index 0\n";
        servoInf[21].pw -= 940;
        gpioServo(servoInf[21].gpio, servoInf[21].pw);
    }
    
    if (current_index == 3){
        std::cout << "open index 0\n";
        servoInf[19].pw -= 940;
        gpioServo(servoInf[19].gpio, servoInf[19].pw);
    }
    
    if (current_index == 4){
        std::cout << "open index 4\n";
        servoInf[23].pw -= 300;
        gpioServo(servoInf[23].gpio, servoInf[23].pw);
        servoInf[12].pw -= 300;
        gpioServo(servoInf[12].gpio, servoInf[12].pw);
        servoInf[21].pw -= 940;
        gpioServo(servoInf[21].gpio, servoInf[21].pw);
        servoInf[19].pw -= 940;
        gpioServo(servoInf[19].gpio, servoInf[19].pw);
    }
}


/**
 * @brief Close the hopper at the current index
 *
 * This method utilizes current index to power the associated servo motor
 * Thus closing the hopper. If the current index is on the multicoloured
 * LED, all hoppers are closed.
 *
 * @throws An Out of Range exception if there are no hoppers to select
 */
void Dispenser::closeDispenser() {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    
    std::cout << "CloseDispenser() has been reached\n";
    
    // TODO: fix softServo errors
    if (current_index == 0){
        std::cout << "close index 0\n";
        servoInf[23].pw += 940;
        gpioServo(servoInf[23].gpio, servoInf[23].pw);
    }
    
    if (current_index == 1){
        std::cout << "close index 1\n";
        servoInf[12].pw += 960;
        gpioServo(servoInf[12].gpio, servoInf[12].pw);
    }
    
    if (current_index == 2){
        std::cout << "open index 0\n";
        servoInf[21].pw += 940;
        gpioServo(servoInf[21].gpio, servoInf[21].pw);
    }
    
    if (current_index == 3){
        std::cout << "open index 0\n";
        servoInf[19].pw += 940;
        gpioServo(servoInf[19].gpio, servoInf[19].pw);
    }
    
    if (current_index == 4){
        std::cout << "open index 4\n";
        servoInf[23].pw += 300;
        gpioServo(servoInf[23].gpio, servoInf[23].pw);
        servoInf[12].pw += 300;
        gpioServo(servoInf[12].gpio, servoInf[12].pw);
        servoInf[21].pw += 940;
        gpioServo(servoInf[21].gpio, servoInf[21].pw);
        servoInf[19].pw += 940;
        gpioServo(servoInf[19].gpio, servoInf[19].pw);
    }
}


/**
 * @brief Appends a pointer to a Hopper object at the end of the hoppers vector.
 *
 * This method is an overload of addHopper that adds an instance of the hopepr class
 * to the end of the hopper vector rather than at a specified index.
 *
 * @param new_hopper An instance of the hopper class to be added to the dispenser
 * @returns The index of the new hopper pointer
 * @throws An Out of Range exception if there are no hoppers to select
 */
int Dispenser::addHopper(Hopper* new_hopper) {
    return this->addHopper(new_hopper, this->size);
}

/**
 * @brief Adds a pointer to a Hopper object at the specified index
 *
 * If an index is provided, the new hopper will be added to the position at new_index
 * modulus the number of hoppers in our system. Otherwise, the new hopper is appended to the end.
 *
 * @param new_hopper An instance of the hopper class to be added to the dispenser
 * @param index The index we want to assign to the hopper
 * @returns The index of the new hopper pointer
 * @throws an Out of Range exception if there are no hoppers to select
 */
int Dispenser::addHopper(Hopper* new_hopper, int index) {
    if (this->size == 0) {
        throw out_of_range("Error: No hoppers available.");
    }
    if (index == this->size) {
        hoppers.push_back(new_hopper);
        this->size++;
    } else {
        this->size++;
        int insert_index = index % this->size;
        hoppers.insert(hoppers.begin() + insert_index, new_hopper);
    }
    return index % this->size;
}

/**
 * @brief Removes the hopper at a specified index in the hopper vector.
 *
 * The hopper at the position at index modulus the number of hoppers in our system will be removed.
 *
 * @param index The index of the hopper to be removed
 */
void Dispenser::removeHopper(int index) {
    this->hoppers.erase(this->hoppers.begin() + (index % this->size));
}

/**
 * @brief Removes a the specified hopper from the dispenser
 *
 * Removes a hopper based on the hopper class instance itself rather than
 * the index of the hopper in the hopper vector
 *
 * @param hopper The hopper class instance to be removed
 */
void Dispenser::removeHopper(Hopper* hopper) {
    vector<Hopper*>::iterator it = std::find(this->hoppers.begin(), this->hoppers.end(), hopper);
    int position = distance(this->hoppers.begin(), it);
    this->removeHopper(position);
}



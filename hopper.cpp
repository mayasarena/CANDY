/**
 * @file hopper.cpp
 * @author Charlie, Marissa, Maya, Fletcher, and Julie
 * @date 28 Nov 2019
 * @brief File the methods for the hopper class
 *
 */

#include "hopper.hpp"
#include <stdbool.h>
using namespace std;

/**
 * @brief hopper constructor creates a hopper
 *
 * Hopper constructor creates a regular hopper for a specific candy type.
 * Last refill time and the multi hopper boolean are specific as well.
 * This particular constructor is for non-multi hoppers.
 *
 * @param string candy_name The name of the candy contained in the hopper
 */
Hopper::Hopper(string candy_name) {
    this->candy_type = candy_name;
    this->last_refill_time = 0;
    this->is_multi_hopper = false;
}

/**
 * @brief hopper constructor creates a multi hopper or regular hopper
 *
 * Hopper constructor has the option to create a multi hopper
 * that can dispense multiple candies at once. Last refill time
 * and multi hopper boolean are specified as well.
 * This constructor can create both regular and multi-hoppers.
 *
 * @param string candy_name The name of the candy type
 * @param bool isMultiHopper True or false for whether it is a multi
 * hopper or not.
 *
 */
Hopper::Hopper(string candy_name, bool isMultiHopper) {
    this->candy_type = candy_name;
    this->last_refill_time = 0;
    this->is_multi_hopper = isMultiHopper;
}

/**
 *@brief this is the hopper destructor
 *
 * Hopper destructor destroys the hopper.
 *
 */
Hopper::~Hopper() {
    
}

/**
 * @brief getHopperID returns the hopper ID
 *
 * getHopperID returns the hopper ID so we know which hopper so the
 * hoppers can easily be managed.
 *
 * @return int hopper_id The hopper id
 */
int Hopper::getHopperID() {
    return this->hopper_id;
}

/**
 * @brief getCandyType returns the candy type
 *
 * getCandyType returns the candy type of the hopper.
 *
 * @return string candy_type The candy type
 */
string Hopper::getCandyType() {
    return this->candy_type;
}

/**
 * @brief getLastRefillTime returns the last refill time
 *
 * getLastRefillTime returns the last refill time of the hopper. This
 * method was going to be used to potentially implement a method of
 * replacing stale candy, however we never got to implement it.
 *
 * @return int last_refill_time The last refill time
 */
int Hopper::getLastRefillTime() {
    return this->last_refill_time;
}

/**
 * @brief setCandyType sets the candy type
 *
 * setCandy type sets the candy type of a hopper. This can be used
 * if a hopper's candy gets replaced with a different type.
 *
 * @param string input The new candy type
 */
void Hopper::setCandyType(string input) {
    this->candy_type = input;
}

/**
 * @brief setLastRefillTime sets the last refill time
 *
 * setLastRefillTime updates the last refill time, which can be used
 * if candy has been replaced.
 *
 * @param int input The last refill time
 */
void Hopper::setLastRefillTime(int input) {
    this->last_refill_time = input;
}

/**
 * @brief isMultiHopper returns whether the hopper is a multi hopper or not
 *
 * isMultiHopper tells us whether or not the hopper is a multi hopper
 * or not. It returns a boolean based on the results.
 *
 * @return is_multi_hopper True if the hopper is a multi hopper and
 * false is the hopper is not.
 */
bool Hopper::isMultiHopper() {
    return this->is_multi_hopper;
}



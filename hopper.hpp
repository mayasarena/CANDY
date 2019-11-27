/**
 * @file hopper.hpp
 * @author Charlie, Marissa, Maya, Fletcher, and Julie
 * @date 28 Nov 2019
 * @brief Header file for hopper class
 *
 */
#ifndef hopper_hpp
#define hopper_hpp

#include <stdio.h>
#include <string>

class Hopper {
public:
    Hopper(std::string candy_name);
    Hopper(std::string candy_name, bool is_multi_hopper);
    ~Hopper();
    int getHopperID();
    int getLastRefillTime();
    std::string getCandyType();
    void setCandyType(std::string new_type);
    void setLastRefillTime(int new_time);
    bool isMultiHopper();
    
protected:
    
private:
    std::string candy_type; ///< type of candy in the hopper
    int last_refill_time; ///< time the hopper was last refilled
    bool is_multi_hopper; ///< true if multi hopper, false elsewise
    int hopper_id; ///< unique ID for a hopper
};
#endif /* hopper_hpp */



//
//  hopper.hpp
//  CandyTesting
//
//  Created by Charlie Pieczonka on 2019-10-30.
//  Copyright © 2019 Team20. All rights reserved.
//

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
    std::string candy_type;
    int last_refill_time;
    bool is_multi_hopper;
    int hopper_id;
};
#endif /* hopper_hpp */



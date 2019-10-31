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
    Hopper(int hopper_id);
    ~Hopper();
    int getHopperID();
    int getLastRefillTime();
    std::string getCandyType();
    void setCandyType(std::string new_type);
    void setLastRefillTime(int new_time);

protected:

private:
    std::string candy_type;
    int last_refill_time;
    boolean is_multi_hopper;
};
#endif /* hopper_hpp */

//
//  hopper.h
//  Header file/prototype for the Hopper class
//@authors
//

#ifndef hopper_h
#define hopper_h
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
};

#endif /* hopper_h */

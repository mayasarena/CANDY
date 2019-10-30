//
//  hopper.h
//  Header file/prototype for the Hopper class
//@authors Charlie,Julie,Maya,Fletcher,Marissa
//

#ifndef hopper_h
#define hopper_h
#include <string>

class Hopper {
    public: //public methods
        Hopper(int hopper_id);
        ~Hopper();
        int getHopperID();
        int getLastRefillTime();
        std::string getCandyType();
        void setCandyType(std::string new_type);
        void setLastRefillTime(int new_time);

    protected:

    private: //private methods
        std::string candy_type;
        int last_refill_time;
};

#endif /* hopper_h */

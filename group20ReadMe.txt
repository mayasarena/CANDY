README CANDY group20

compile: g++ dispenser.cpp dispenser.hpp hopper.cpp hopper.hpp main.cpp -o project -lwiringPi

The output file will run and show the structure, no arguments or runtime instruction needed

(servos did not deliver, so print statements are in place of servos moving to dispense candy)

comments that say "button pressed" are simulating a button input, and the algorithm continues accordingly. Our dispense algorithm
normally will loop forever and dispense on press, but our prototype shows single dispense command before terminating.
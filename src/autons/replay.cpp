//Includes
#include "../src/globals.hpp"
#include "../src/autons/autons.hpp"
#include "../src/control/movement.hpp"

//Method definition
void replay(){
     //Load file
     std::ifstream file("/usd/sigma.auton", std::ios::binary);

     //Iterate through inputs
     for (int i = 0; i < INPUT_COUNT; i++){
         //Load bytes
         int inputs[14];
         char byte;
         for (int i = 0; i < 14; i++){
             file.read(&byte, 1);
             inputs[i] = int8_t(byte);
         }

         //Pass and delay
         movement(inputs);
         pros::delay(50);
     }

     //End movement
     int inputs[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
     movement(inputs);
}
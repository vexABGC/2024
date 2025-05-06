//Includes
#include "main.h" // IWYU pragma: keep
#include "../src/globals.hpp"
#include "../src/autons/autons.hpp"

//Method definition
void blueSafeMogo() {
    std::cout << "Blue Safe Mogo" << std::endl;
    chassis.odom_x_flip();
    chassis.odom_theta_flip();
    safeMogo();
}
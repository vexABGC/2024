//Includes
#include "main.h" // IWYU pragma: keep
#include "../src/globals.hpp"
#include "../src/autons/autons.hpp"

//Method definition
void redSafeRing() {
    std::cout << "Red Safe Ring" << std::endl;
    chassis.odom_x_flip();
    chassis.odom_theta_flip();
    safeRing();
}
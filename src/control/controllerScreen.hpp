//Includes
#include <string>
#include <vector>

//Method Declaration
void raiseControllerWarning(std::string line1, std::string line2, std::string vibration, int duration);
void raiseControllerWarning(std::string errorText);
void updateLines();
std::vector<std::string> getOverheatingMotors();
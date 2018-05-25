#include "navigation_engine.hpp"
#include "navigation_path.hpp"
#include "wrap-hwlib.hpp"
#include <string>

NavigationEngine::NavigationEngine() {
}

void NavigationEngine::run() {
    NavigationPath path;
    while (true) {
        std::string tempString;
        std::string tempString2;
        hwlib::cout << "Please input the x position\n";
        tempString << hwlib::cin;
        auto input1 = tempString.itoi();
        hwlib::cout << "Please input the y position\n";
        tempString2 << hwlib::cin;
        auto input2 = tempString2.itoi();
        path.addPathLocation({float(input1), float(input2)});
        auto nextLocation = path.getNextLocation();
        hwlib::cout << int(nextLocation.x) << ',' << int(nextLocation.y) << " added to the path." << hwlib::endl;
        hwlib::cout << "Next point is 3 meters forward, 40 degrees rotation right" << hwlib::endl;
    }
    // while (true) {
    /*IDLE STATE*/
    // 1 wait for input
    // 2 check type of input > change state
    /*MOVING STATE*/
    // 3 if input is path data
    // 4 check current location
    // 5 calculate distance to next location
    // 6 calculate rotation to next point from current viewing angle.
    // 7 send distance/rotation out via IOInterface
    // 8 wait for confirmation of movement
    // 9 repeat 4-9 while there is path data
    // 10 return to idle state
    //}
}

void NavigationEngine::onReceive(const Command &command) {
}

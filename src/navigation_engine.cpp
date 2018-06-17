#include "navigation_engine.hpp"
#include "navigation_path.hpp"
#include "wrap-hwlib.hpp"
#include <string>

NavigationEngine::NavigationEngine() {
}

void NavigationEngine::run() {
    NavigationPath path;
    while (true) {
        hwlib::cout << "Please input the x position\r\n";
        auto input1 = hwlib::uart_getc() - '0';
        hwlib::cout << "Please input the y position\r\n";
        auto input2 = hwlib::uart_getc() - '0';
        path.addPathLocation({float(input1), float(input2)});
        hwlib::cout << input1 << ',' << input2 << " added to the path." << hwlib::endl;
        if (path.getPathLength() > 1) {
            path.getNextLocation();
            path.getNextLocation();
            hwlib::cout << "Next point is 3 meters forward, 40 degrees rotation right" << hwlib::endl;
        }
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
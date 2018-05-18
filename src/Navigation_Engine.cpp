#include "Navigation_Engine.hpp"
#include "Navigation_Path.hpp"
#include "wrap-hwlib.hpp"

NavigationEngine::NavigationEngine() {
}

void NavigationEngine::run() {
    /* This code is temporary */
    NavigationPath path;
    path.addPathLocation({0, 5});
    path.addPathLocation({6, 8});
    path.addPathLocation({-123, 25});
    auto location = path.getNextLocation();
    hwlib::cout << int(location.x) << ',' << int(location.y) << hwlib::endl;
    location = path.getNextLocation();
    hwlib::cout << int(location.x) << ',' << int(location.y) << hwlib::endl;
    location = path.getNextLocation();
    hwlib::cout << int(location.x) << ',' << int(location.y) << hwlib::endl;
    /* End temporary code */
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
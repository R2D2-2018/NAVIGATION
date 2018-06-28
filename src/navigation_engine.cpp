#include "navigation_engine.hpp"
#include "navigation_path.hpp"
#include "wrap-hwlib.hpp"

NavigationEngine::NavigationEngine() {
}

void NavigationEngine::run() {
    NavigationPath path;
    while (true) {
        hwlib::cout << "Please input the x position\n";
        auto input1 = hwlib::uart_getc() - '0';
        hwlib::cout << "Please input the y position\n";
        auto input2 = hwlib::uart_getc() - '0';
        path.addPathLocation({float(input1), float(input2)});
        hwlib::cout << input1 << ',' << input2 << " added to the path." << hwlib::endl;
        if (path.getPathLength() > 1) {
            path.getNextLocation();
            path.getNextLocation();
            hwlib::cout << "Next point is 3 meters forward, 40 degrees rotation right" << hwlib::endl;
        }
    }
}

void NavigationEngine::onReceive(const Command &command) {
}
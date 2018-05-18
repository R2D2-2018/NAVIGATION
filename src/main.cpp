#include "IO_Interface.hpp"
#include "Navigation_Engine.hpp"
#include "Vector2f.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    NavigationEngine engine;
    IOInterface interface(engine);
    hwlib::wait_ms(1000);
    engine.run();
    Vector2f point1(1.5, 5.6);
    hwlib::cout << int(point1.x) << ',' << int(point1.y) << hwlib::endl;
    hwlib::cout << "HWLIB does not support floats.." << hwlib::endl;
}

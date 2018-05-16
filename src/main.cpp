#include "IO_Interface.hpp"
#include "Navigation_Engine.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    NavigationEngine engine;
    IOInterface interface(engine);
    hwlib::wait_ms(1000);
    hwlib::cout << "Hello world!" << hwlib::endl;
}

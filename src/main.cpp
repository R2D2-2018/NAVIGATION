#include "IO_Interface.hpp"
#include "Navigation_Engine.hpp"
#include "wrap-hwlib.hpp"
#include "Vector2f.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    NavigationEngine engine;
    IOInterface interface(engine);
    hwlib::wait_ms(1000);
	Vector2f point1(1.5, 5.6);
	std::cout << point1.x << ',' << point1.y << std::endl;
}

#include "io_interface.hpp"
#include "mpu9250_interface.hpp"
#include "navigation_engine.hpp"
#include "vector2f.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    NavigationEngine engine;
    IOInterface interface(engine);
    hwlib::wait_ms(1000);
    Vector2f point1(1.5, 5.6);
    hwlib::cout << int(point1.x) << ',' << int(point1.y) << hwlib::endl;
    hwlib::cout << "HWLIB does not support floats.." << hwlib::endl;

    auto scl = due::pin_oc(due::pins::scl);
    auto sda = due::pin_oc(due::pins::sda);

    const int8_t address = 0x68;

    MPU9250Interface SENSOR(scl, sda, address);
    SENSOR.init();

    return 0;
}

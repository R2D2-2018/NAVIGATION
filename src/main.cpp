#include "io_interface.hpp"
#include "mpu9250_interface.hpp"
#include "navigation_engine.hpp"
#include "vector2f.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    auto scl = due::pin_oc(due::pins::scl);
    auto sda = due::pin_oc(due::pins::sda);
    const uint8_t address = 0x68;

    NavigationEngine engine;
    IOInterface interface(engine);
    MPU9250Interface sensor(scl, sda, address);
    sensor.init();
    hwlib::wait_ms(10000);
    hwlib::cout << "starting calibration" << hwlib::endl;
    sensor.calibrateMagnetometer();
    // engine.run();
    return 0;
}

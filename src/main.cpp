#include "io_interface.hpp"
#include "mpu9250_interface.hpp"
#include "navigation_engine.hpp"
#include "vector2f.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    const int8_t address = 0x68;

    NavigationEngine engine;
    IOInterface interface(engine);
    MPU9250Interface sensor(scl, sda, address);

    for (;;) {
        hwlib::cout << "Accelerator: \r\n";
        hwlib::cout << sensor.getAccelerationValues().getX() << "|" << sensor.getAccelerationValues().getY() << "|"
                    << sensor.getAccelerationValues().getZ() << "\r\n";
        hwlib::cout << "Gyroscope: \r\n";
        hwlib::cout << sensor.getGyroscopeValues().getX() << "|" << sensor.getGyroscopeValues().getY() << "|"
                    << sensor.getGyroscopeValues().getZ() << "\r\n";
        hwlib::cout << "Magnetometer: \r\n";
        hwlib::cout << sensor.getMagnetometerValues().getX() << "|" << sensor.getMagnetometerValues().getY() << "|"
                    << sensor.getMagnetometerValues().getZ() << "\r\n";

        hwlib::cout << "\r\n";
        hwlib::wait_ms(1000);
    }
    // engine.run();
    return 0;
}

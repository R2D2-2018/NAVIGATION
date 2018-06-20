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
        // hwlib::cout << "Gyroscope: \r\n";
        // hwlib::cout << sensor.getGyroscopeValues().getX() << "|" << sensor.getGyroscopeValues().getY() << "|"
        //             << sensor.getGyroscopeValues().getZ() << "\r\n";
        // hwlib::cout << "Accelerator: \r\n";
        // hwlib::cout << (int)sensor.getAccelerationValues().getX() << "|" << (int)sensor.getAccelerationValues().getY() << "|"
        //             << (int)sensor.getAccelerationValues().getZ() << "\r\n";
        hwlib::cout << "Magnetometer: \r\n";
        hwlib::cout << (int)sensor.getMagnetometerCalibrateValues().getX() << "|"
                    << (int)sensor.getMagnetometerCalibrateValues().getY() << "|"
                    << (int)sensor.getMagnetometerCalibrateValues().getZ() << "\r\n";

        hwlib::cout << "\r\n";
        hwlib::wait_ms(1000);
    }
    return 0;
}

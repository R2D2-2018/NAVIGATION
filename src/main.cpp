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
    double x, y, z;

    NavigationEngine engine;
    IOInterface interface(engine);
    MPU9250Interface sensor(scl, sda, address);
    sensor.calibrate();

    for (;;) {
        x = (double(sensor.getAccelerationValues().getX()) / 16384) * 1000;
        y = (double(sensor.getAccelerationValues().getY()) / 16384) * 1000;
        z = (double(sensor.getAccelerationValues().getZ()) / 16384) * 1000;

        hwlib::cout << "Accelerator: \r\n"
                    << " X: " << (sensor.getAccelerationValues().getX()) << "\r\n"
                    << " Y: " << (sensor.getAccelerationValues().getY()) << "\r\n"
                    << " Z: " << (sensor.getAccelerationValues().getZ()) << "\r\n";

        hwlib::cout << "Accelerator corrected: \r\n"
                    << " X: " << (sensor.getAccelerationValues().getX() + sensor.getAccelerationCalibrateValues().getX()) << "\r\n"
                    << " Y: " << (sensor.getAccelerationValues().getY() + sensor.getAccelerationCalibrateValues().getY()) << "\r\n"
                    << " Z: " << (sensor.getAccelerationValues().getZ() + sensor.getAccelerationCalibrateValues().getZ()) << "\r\n";

        hwlib::cout << "Gyroscope: \r\n"
                    << sensor.getGyroscopeValues().getX() << "|" << sensor.getGyroscopeValues().getY() << "|"
                    << sensor.getGyroscopeValues().getZ() << "\r\n";

        hwlib::cout << "Magnetometer: \r\n"
                    << sensor.getMagnetometerValues().getX() << "|" << sensor.getMagnetometerValues().getY() << "|"
                    << sensor.getMagnetometerValues().getZ() << "\r\n";

        hwlib::cout << "\r\n";
        hwlib::wait_ms(1000);
    }
    return 0;
}

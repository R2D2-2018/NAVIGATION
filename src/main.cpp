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
    // auto x, y, z;

    NavigationEngine engine;
    IOInterface interface(engine);
    MPU9250Interface sensor(scl, sda, address);
    sensor.calibrate();

    for (int i = 0; i < 20; i++) {
        auto x = (float(sensor.getAccelerationValues().getX()) / 16384) * 1000;
        auto y = (float(sensor.getAccelerationValues().getY()) / 16384) * 1000;
        auto z = (float(sensor.getAccelerationValues().getZ()) / 16384) * 1000;
        hwlib::cout << "Accelerator: \r\n";
        sensor.printValuesX_Y_Z(sensor.getAccelerationValues());
        sensor.printAccelerationGravity(sensor.getAccelerationValues());

        hwlib::cout << "Accelerator corrected: \r\n"
                    << " X: " << (sensor.getAccelerationValues().getX() - sensor.getAccelerationCalibrateValues().getX()) << "\r\n"
                    << " Y: " << (sensor.getAccelerationValues().getY() - sensor.getAccelerationCalibrateValues().getY()) << "\r\n"
                    << " Z: " << (sensor.getAccelerationValues().getZ() - sensor.getAccelerationCalibrateValues().getZ()) << "\r\n";
        sensor.printAccelerationGravity();

        hwlib::cout << "Gyroscope: \r\n"
                    << " X: " << sensor.getGyroscopeValues().getX() << "Degree/sec \r\n"
                    << " Y: " << sensor.getGyroscopeValues().getY() << "Degree/sec \r\n"
                    << " Z: " << sensor.getGyroscopeValues().getZ() << "Degree/sec \r\n";

        hwlib::cout << "Gyroscope corrected: \r\n"
                    << " X: " << (sensor.getGyroscopeValues().getX() - sensor.getGyroscopeCalibrateValues().getX())
                    << "Degree/sec \r\n"
                    << " Y: " << (sensor.getGyroscopeValues().getY() - sensor.getGyroscopeCalibrateValues().getY())
                    << "Degree/sec \r\n"
                    << " Z: " << (sensor.getGyroscopeValues().getZ() - sensor.getGyroscopeCalibrateValues().getZ())
                    << "Degree/sec \r\n";

        hwlib::cout << "Magnetometer: \r\n"
                    << sensor.getMagnetometerValues().getX() << "|" << sensor.getMagnetometerValues().getY() << "|"
                    << sensor.getMagnetometerValues().getZ() << "\r\n";

        hwlib::cout << "\r\n";
        hwlib::wait_ms(1000);
    }
    return 0;
}

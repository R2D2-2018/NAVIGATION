#include "io_interface.hpp"
#include "mpu9250_interface.hpp"
#include "navigation_engine.hpp"
#include "vector2f.hpp"
#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    auto scl = due::pin_oc(due::pins::scl);
    auto sda = due::pin_oc(due::pins::sda);
    const int8_t address = 0x68;

    NavigationEngine engine;
    IOInterface interface(engine);
    hwlib::wait_ms(1000);
    Vector2f point1(1.5, 5.6);
    hwlib::cout << int(point1.x) << ',' << int(point1.y) << hwlib::endl;
    // hwlib::cout << "HWLIB does not support floats.." << hwlib::endl;

    MPU9250Interface sensor(scl, sda, address);
    sensor.init();

    hwlib::cout << "Get values:\nPress 1 for gyroscope output\nPress 2 for accelerator output\nPress 3 for magnetometer output\n";
    for (;;) {
        char i;
        hwlib::cin >> i;

        switch (i) {
        case '1': {
            hwlib::cout << "Gyroscope: ";
            sensor.getGyro();
            break;
        }
        case '2': {
            hwlib::cout << "Accelerator: ";
            sensor.getAccel();
            break;
        }
        case '3': {
            hwlib::cout << "Magnetometer: ";
            sensor.getMagn();

            break;
        }
        default:
            hwlib::cout << hwlib::right << "Invalid input\n";
        }
    }

    return 0;
}
#include "io_interface.hpp"
#include "mpu9250_interface.hpp"
#include "navigation_engine.hpp"
#include "path.hpp"
#include "polar_vector2f.hpp"
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
    Path path(sensor);

    PolarVector2f goTo = PolarVector2f();
    float goToAngle;
    float goToDistance;

    for (;;) {
        goTo = path.getDirections(Vector2f(2, 4), Vector2f(4, 8));
        goToAngle = goTo.getAngle();
        goToDistance = goTo.getDistance();

        hwlib::cout << "Gyroscope: \r\n";
        hwlib::cout << (int)sensor.getGyroscopeValues().getX() << "|" << (int)sensor.getGyroscopeValues().getY() << "|"
                    << (int)sensor.getGyroscopeValues().getZ() << "\r\n";
        hwlib::cout << "Accelerator: \r\n";
        hwlib::cout << (int)sensor.getAccelerationValues().getX() << "|" << (int)sensor.getAccelerationValues().getY() << "|"
                    << (int)sensor.getAccelerationValues().getZ() << "\r\n";
        hwlib::cout << "Magnetometer: \r\n";
        hwlib::cout << (int)sensor.getMagnetometerValues().getX() << " | " << (int)sensor.getMagnetometerValues().getY() << " | "
                    << (int)sensor.getMagnetometerValues().getZ() << " | ";

        hwlib::cout << "Directions: \r\n";
        hwlib::cout << "Angle : " << (int)(goToAngle) << "." << (int)((goToAngle - (int)(goToAngle)) * 1000) << "\r\n";
        hwlib::cout << "Distance : " << (int)(goToDistance * 100) << "\r\n";
        hwlib::cout << "\r\n";

        hwlib::wait_ms(1000);
    }
    return 0;
}

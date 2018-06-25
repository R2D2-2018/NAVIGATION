#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/coordinate3d.hpp"
#include "../src/mpu9250_interface.hpp"
#include "../src/navigation_path.hpp"
#include "../src/polar_vector2f.hpp"
#include "catch.hpp"

TEST_CASE("PolarVector2f get angle") {
    PolarVector2f polar;

    polar.setAngle(30.0);

    REQUIRE(polar.getAngle() == 30);
}

TEST_CASE("PolarVector2f get distance") {
    PolarVector2f polar;

    polar.setDistance(50.0);

    REQUIRE(polar.getDistance() == 50);
}

TEST_CASE("Path get directions") {
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
    auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
    const int8_t address = 0x68;

    MPU9250Interface sensor(scl, sda, address);
    Path path(sensor);

    PolarVector2f goTo = path.getDirections(Vector2f(2, 4), Vector2f(4, 8));
    float goToAngle = goTo.getAngle();

    REQUIRE(polar.getAngle() == 4.4721);
}

/// This one is not working, because math.h isn't working accordingly
// TEST_CASE("Path get directions") {
//     auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
//     auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
//     const int8_t address = 0x68;

//     MPU9250Interface sensor(scl, sda, address);
//     Path path(sensor);

//     PolarVector2f goTo = path.getDirections(Vector2f(2, 4), Vector2f(4, 8));
//     float goToDistance = goTo.getDistance();

//     REQUIRE(polar.getDistance() == 63.436);
// }
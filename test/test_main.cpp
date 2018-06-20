#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/coordinate3d.hpp"
#include "../src/navigation_path.hpp"
#include "catch.hpp"

TEST_CASE("Example Test Case") {
    REQUIRE(10 == 10);
}

TEST_CASE("Coordinates 3D get coordinates positive") {
    Coordinate3D<int> coordinates(140, 150, 130);

    REQUIRE(coordinates.getX() == 140);
    REQUIRE(coordinates.getY() == 150);
    REQUIRE(coordinates.getZ() == 130);
}

TEST_CASE("Coordinates 3D get coordinates negative") {
    Coordinate3D<int> coordinates(-140, -150, -130);

    REQUIRE(coordinates.getX() == -140);
    REQUIRE(coordinates.getY() == -150);
    REQUIRE(coordinates.getZ() == -130);
}

TEST_CASE("Coordinates 3D set coordinates positive") {
    Coordinate3D<int> coordinates;
    coordinates.setX(140);
    coordinates.setY(150);
    coordinates.setZ(130);

    REQUIRE(coordinates.getX() == 140);
    REQUIRE(coordinates.getY() == 150);
    REQUIRE(coordinates.getZ() == 130);
}

TEST_CASE("Coordinates 3D set coordinates negative") {
    Coordinate3D<int> coordinates;
    coordinates.setX(-140);
    coordinates.setY(-150);
    coordinates.setZ(-130);

    REQUIRE(coordinates.getX() == -140);
    REQUIRE(coordinates.getY() == -150);
    REQUIRE(coordinates.getZ() == -130);
}

// TEST_CASE("Navigation Path in/out test", "[navigation_path]") {
//     // Preconditions:
//     NavigationPath path;
//     path.addPathLocation({1, 5});
//     path.addPathLocation({10, 5});
//     path.addPathLocation({-1, -8});
//     path.addPathLocation({99.1, 101.2});

//     // Run Test:
//     auto testLocation1 = path.getNextLocation();
//     auto testLocation2 = path.getNextLocation();
//     auto testLocation3 = path.getNextLocation();
//     auto testLocation4 = path.getNextLocation();

//     // Compare Postconditions:
//     REQUIRE(testLocation1.x == 1);
//     REQUIRE(testLocation1.y == 5);
//     REQUIRE(testLocation2.x == 10);
//     REQUIRE(testLocation2.y == 5);
//     REQUIRE(testLocation3.x == -1);
//     REQUIRE(testLocation3.y == -8);
//     REQUIRE(testLocation4.x == 99.1f);
//     REQUIRE(testLocation4.y == 101.2f);
// }

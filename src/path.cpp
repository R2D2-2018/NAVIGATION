#include "path.hpp"

Path::Path(MPU9250Interface mpu9250) : mpu9250(mpu9250) {
}

PolarVector2f Path::convertCartesianToPolar(Vector2f node) {
    PolarVector2f polar;
    double angle;
    double distance;

    angle = m.atan(node.getY() / node.getX());
    distance = m.sqrt((m.pow(node.getX(), 2), m.pow(node.getY(), 2)));
    polar.setAngle(angle);
    polar.setDistance(distance);

    return polar;
}

float Path::getRotationFromMPU() {
    float rotation;
    Coordinate3D<float> rotation3D = mpu9250.getMagnetometerValues();
    rotation = rotation3D.getY();
    return rotation;
}

PolarVector2f Path::getDirections(Vector2f currentPosition, Vector2f nextPosition) {
    // 1. Get current rotation in degrees.
    // 2. Calculate the difference between the desired rotation and the current rotation from the compass (in degrees).
    // 3. Get current location from something.
    // 4. Calculate the difference between desired location and current location.
    PolarVector2f directions;

    float deltaX = nextPosition.getX() - currentPosition.getX();
    float deltaY = nextPosition.getY() - currentPosition.getY();

    float angle = m.atan(deltaY / deltaX) * 180 / m.pi;
    float distance = m.sqrt(m.pow(deltaX, 2) + m.pow(deltaY, 2));

    directions.setAngle(angle);
    directions.setDistance(distance);

    return directions;
}
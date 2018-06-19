#include "path.hpp"

Path::Path() {
}

PolarVector2f Path::convertCartesianToPolar(Vector2f node) {
    PolarVector2f polar;
    double angle;
    double distance;
    angle = atan(node.getY() / node.getX());
    distance = sqrt((pow(node.getX(), 2), pow(node.getY(), 2)));
    polar.setAngle(angle);
    polar.setDistance(distance);
}

double Path::calculateToGoDirection(Vector2f node) {
    PolarVector2f polar = convertCartesianToPolar(node);
    // float deltaX = positionX - node.getX();
    // float deltaY = positionY - node.getY();

    // 1. Get current rotation in degrees.
    // 2. Calculate the difference between the desired rotation and the current rotation from the compass (in degrees).
    // 3. Get current location from something.
    // 4. Calculate the difference between desired location and current location.
}
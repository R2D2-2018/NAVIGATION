#include "polar_vector2f.hpp"

float PolarVector2f::getAngle() {
    return angle;
}

float PolarVector2f::getDistance() {
    return distance;
}

void PolarVector2f::setAngle(float value) {
    angle = value;
}

void PolarVector2f::setDistance(float value) {
    distance = value;
}
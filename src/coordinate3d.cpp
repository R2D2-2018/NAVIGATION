#include "coordinate3d.hpp"

Coordinate3D::Coordinate3D() : x(0), y(0), z(0) {
}

template <typename T>
Coordinate3D::Coordinate3D(T x, T y, T z) : x(x), y(y), z(z) {
}

template <typename T>
void Coordinate3D::setX(T value) {
    x = value;
}

template <typename T>
void Coordinate3D::setY(T value) {
    y = value;
}

template <typename T>
void Coordinate3D::setZ(T value) {
    z = value;
}

template <typename T>
T Coordinate3D::getX() {
    return x;
}

template <typename T>
T Coordinate3D::getY() {
    return y;
}

template <typename T>
T Coordinate3D::getZ() {
    return z;
}
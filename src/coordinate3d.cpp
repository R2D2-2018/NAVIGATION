#include "coordinate3d.hpp"

Coordinate3D::Coordinate3D() : x(0), y(0), z(0) {
}

Coordinate3D::Coordinate3D(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {
}

void Coordinate3D::setX(int16_t value) {
    x = value;
}

void Coordinate3D::setY(int16_t value) {
    y = value;
}

void Coordinate3D::setZ(int16_t value) {
    z = value;
}

int16_t Coordinate3D::getX() {
    return x;
}

int16_t Coordinate3D::getY() {
    return y;
}

int16_t Coordinate3D::getZ() {
    return z;
}

Coordinate3D &Coordinate3D::operator+=(const Coordinate3D &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Coordinate3D &Coordinate3D::operator-=(const Coordinate3D &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Coordinate3D &Coordinate3D::operator*=(const int multiplier) {
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
    return *this;
}

Coordinate3D &Coordinate3D::operator/=(const int divider) {
    x /= divider;
    y /= divider;
    z /= divider;
    return *this;
}

Coordinate3D Coordinate3D::operator+(const Coordinate3D &rhs) const {
    Coordinate3D temp = *this;
    temp += rhs;
    return temp;
}

Coordinate3D Coordinate3D::operator-(const Coordinate3D &rhs) const {
    Coordinate3D temp = *this;
    temp -= rhs;
    return temp;
}
Coordinate3D Coordinate3D::operator/(const int divider) const {
    Coordinate3D temp = *this;
    temp /= divider;
    return temp;
}

Coordinate3D Coordinate3D::operator*(const int multiplier) const {
    Coordinate3D temp = *this;
    temp *= multiplier;
    return temp;
}
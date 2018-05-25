#include "navigation_path.hpp"

NavigationPath::NavigationPath() {
}
void NavigationPath::addPathLocation(Vector2f location) {
    path[index] = location;
    index++;
    if (index >= 50) {
        index = 0;
    }
}
Vector2f NavigationPath::getNextLocation() {
    auto nextLocation = path[head];
    head++;
    if (head >= 50) {
        head = 0;
    }
    return nextLocation;
}

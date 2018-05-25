/**
 * @file
 * @brief     NavigationPath Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef NAVIGATION_PATH_HPP
#define NAVIGATION_PATH_HPP

#include "vector2f.hpp"
#include <vector>

class NavigationPath {
  public:
    NavigationPath();
    void addPathLocation(Vector2f location);
    Vector2f getNextLocation();
    int getPathLength();

  private:
    Vector2f path[50];
    unsigned index = 0;
    unsigned head = 0;
};

#endif

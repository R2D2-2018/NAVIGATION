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
    /**
     * @brief creates a NavigationPath object.
     *
     * Constructor for a NavigationPath object without arguments.
     *
     * @return a NavigationPath object.
     */
    NavigationPath();
	
	/**
     * @brief adds a Vector2f to the path.
     * 
	 * adds a Vector2f to the back of the current path.
     *
     * @param[in]    location    a Vector2f signifying a location
     * @return void
     */
    void addPathLocation(Vector2f location);
	
    /**
     * @brief gets the next location from the path.
     * 
	 * gets the Vector2f at the front of the current path.
     *
     * @return Vector2f
     */
    Vector2f getNextLocation();
	
    /**
     * @brief gets the length of the path.
     * 
	 * gets the current length of the path.
     *
     * @return int
     */	
    int getPathLength();

  private:
    Vector2f path[50];
    unsigned index = 0;
    unsigned head = 0;
};

#endif

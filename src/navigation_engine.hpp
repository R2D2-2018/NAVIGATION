/**
 * @file
 * @brief     NavigationEngine Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef NAVIGATION_ENGINE_HPP
#define NAVIGATION_ENGINE_HPP

#include "io_interface_listener.hpp"
#include "position_module.hpp"

class NavigationEngine : public IOInterfaceListener {
  public:
    /**
     * @brief creates a NavigationEngine object
     *
     * Constructor for a NavigationEngine object without arguments.
     *
     * @return a NavigationEngine object
     */
    NavigationEngine() {
    }
    void run();

  private:
    /**
     * @brief listener function called when receiving events.
     *
     * function called by the IOInterface when receiving events. Redefines onReceive(const Command &command) in
     * io_interface_listener.hpp
     *
     * @param[in]    command    a const Command reference
     * @return void
     */
    void onReceive(const Command &command) {
    }
    PositionModule positionModule;
};

#endif

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
    NavigationEngine();

    /**
     * @brief Main loop for this thread
     *
     * This function is called when the program starts and can only be ended by shutting down the program.
     *
     * @return void
     */
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
    void onReceive(const Command &command);
    PositionModule positionModule;
};

#endif

/**
 * @file
 * @brief     NavigationEngine Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef NAVIGATION_ENGINE_HPP
#define NAVIGATION_ENGINE_HPP

#include "IO_Interface_Listener.hpp"
#include "Position_Module.hpp"

class NavigationEngine : public IOInterfaceListener {
  public:
    NavigationEngine();
    void run();

  private:
    void onReceive(const Command &command);
    PositionModule positionModule;
};

#endif
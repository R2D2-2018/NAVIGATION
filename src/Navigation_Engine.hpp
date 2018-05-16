#ifndef NAVIGATION_ENGINE_HPP
#define NAVIGATION_ENGINE_HPP

#include "IO_Interface_Listener.hpp"
#include "Position_Module.hpp"

class NavigationEngine : public IOInterfaceListener {
  public:
    NavigationEngine() {
    }

  private:
    void onReceive(const Command &command) {
    }
    PositionModule positionModule;
};

#endif
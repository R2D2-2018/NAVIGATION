#ifndef IO_INTERFACE_HPP
#define IO_INTERFACE_HPP

#include "Command.hpp"

class IOInterfaceListener;

class IOInterface {
  public:
    IOInterface(IOInterfaceListener &listener) : listener(listener) {
    }

  private:
    IOInterfaceListener &listener;
};

#endif
/**
 * @file
 * @brief     IOInterface Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef IO_INTERFACE_HPP
#define IO_INTERFACE_HPP

#include "command.hpp"

class IOInterfaceListener;

class IOInterface {
  public:
    IOInterface(IOInterfaceListener &listener) : listener(listener) {
    }

  private:
    IOInterfaceListener &listener;
};

#endif
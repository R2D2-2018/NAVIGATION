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
    /**
     * @brief creates an IOInterface object
     *
     * Constructor for an IOInterface object with a IOInterfaceListener reference as argument.
     *
     * @param[in]    listener    A reference to an IOInterfaceListener object.
     *
     * @return an IOInterface object
     */
    IOInterface(IOInterfaceListener &listener) : listener(listener) {
    }

  private:
    IOInterfaceListener &listener;
};

#endif
/**
 * @file
 * @brief     IOInterfaceListener Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef IO_INTERFACE_LISTENER_HPP
#define IO_INTERFACE_LISTENER_HPP

#include "Command.hpp"

class IOInterfaceListener
{
	virtual void onReceive(const Command& command);
};

#endif
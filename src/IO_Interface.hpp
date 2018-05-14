#ifndef IO_INTERFACE_HPP
#define IO_INTERFACE_HPP

#include "Command.hpp"

class IOInterfaceListener;

class IOInterface
{
public:
    IOInterface(){}
private:
	IOInterfaceListener &listener;
};

#endif
#ifndef NAVIGATION_ENGINE_HPP
#define NAVIGATION_ENGINE_HPP

#include "IO_Interface_Listener.hpp"

class NavigationEngine : public IOInterfaceListener
{
public:
    NavigationEngine(){}
private:
	void onReceive(const Command& command){}
};

#endif
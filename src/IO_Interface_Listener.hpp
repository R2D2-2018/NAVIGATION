/**
 * @file
 * @brief     IOInterfaceListener Class
 * @author    Quinten Perquin
 * @license   See LICENSE
 */

#ifndef IO_INTERFACE_LISTENER_HPP
#define IO_INTERFACE_LISTENER_HPP

#include "Command.hpp"

class IOInterfaceListener {
    /**
     * @brief virtual listener function called when receiving events.
     *
     *
     * [BLANK]
     * @param[in]    command    a const Command reference
     * @return void
     */
    virtual void onReceive(const Command &command);
};

#endif
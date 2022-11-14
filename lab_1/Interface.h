#pragma once

#ifndef INTERFACE_H
#define INTERFACE_H

#include "Operations.h"

class Interface {
public:
    Interface();
    bool GetCommand();
    void GetId();
    void GetField();
    void SeparationOfParameters();
    bool DoCommand();
private:
    std::unique_ptr<Operations> m_tools;
    std::string m_command;
    std::vector<std::string> m_tokens;
    size_t comm;
    size_t tabll;
};


#endif 

#include <iostream>

#include "Interface.h"

Interface::Interface() {
    m_tools = std::make_unique<Operations>();
}

bool Interface::GetCommand() {
    std::cout << "Choose a function:\n0 - STOP\n1 - INSERT\n2 - UPDATE\n3 - GET-M\n4 - GET-S\n5 - DELETE\n6 - PRINT" << std::endl;
    std::cin >> comm;
    if (comm) {
        std::cout << "Choose a table:\n1 - SERVICE\n2 - PATIENT\n3 - DOCTOR\n4 - DEPARTMENT\n5 - CABINET\n6 - CARD" << std::endl;
        std::cin >> tabll;
    }

    return DoCommand();
}

void Interface::GetId() {
    std::cout << "Specify the ID:" << std::endl;
    std::cin.ignore();
    std::string id;
    std::getline(std::cin, id);
    m_tokens.push_back(id);
}

void Interface::GetField() {
    std::cout << "Specify the field name:" << std::endl;
    std::string field;
    std::getline(std::cin, field);
    m_tokens.push_back(field);
}

void Interface::SeparationOfParameters() {
    m_tokens = {};
    std::string token = "";
    for (int i = 0; i < m_command.length(); i++) {
        if (m_command[i] == ' ') {
            m_tokens.push_back(token);
            token = "";
        }
        else {
            token.push_back(m_command[i]);
        }
    }
    m_tokens.push_back(token);
}


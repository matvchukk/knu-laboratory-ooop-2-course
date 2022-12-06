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

bool Interface::DoCommand() {
    if (comm == 0)  return false;
    std::string table_name;
    switch (tabll) {
    case 1:
        table_name = "SERVICE";
        std::cout << "Parameters: CABINET_ID, DOCTOR_ID, NAME, DATE, PRICE\n" << std::endl;
        break;
    case 2:
        table_name = "PATIENT";
        std::cout << "Parameters: FIRST_NAME, LAST_NAME, FATHER_NAME, PHONE_NUMBER, FAMILY_DOCTOR, MEDICAL_CARD\n" << std::endl;
        break;
    case 3:
        table_name = "DOCTOR";
        std::cout << "Parameters: FIRST_NAME, LAST_NAME, FATHER_NAME, SPECIALIZATION, EXPERIENCE, CATEGORY\n" << std::endl;
        break;
    case 4:
        table_name = "DEPARTMENT";
        std::cout << "Parameters: NAME, HEAD\n" << std::endl;
        break;
    case 5:
        table_name = "CABINET";
        std::cout << "Parameters: NUMBER, FLOOR, EQUIPMENT\n" << std::endl;
        break;
    case 6:
        table_name = "CARD";
        std::cout << "Parameters: SERVICE, DIAGNOSIS, MED_HISTORY\n" << std::endl;
        break;
    default:
        break;
    }
    if (comm == 1) {
        if (!m_tokens.empty())  m_tokens = {};
        std::cout << "Specify the parameters: " << std::endl;
        std::cin.ignore();
        std::getline(std::cin, m_command);
        SeparationOfParameters();
        try {
            m_tools->Add_m(table_name, m_tokens);
        }
        catch (std::exception& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
        }
    }
    else if (comm == 2) {
        if (!m_tokens.empty()) m_tokens = {};
        GetId();
        GetField();
        std::cout << "Specify the parameter: " << std::endl;
        std::string parameter;
        std::getline(std::cin, parameter);
        m_tokens.push_back(parameter);
        try {
            m_tools->Update(table_name, m_tokens);
        }
        catch (std::exception& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
        }
    }
    else if (comm == 3) {
        if (!m_tokens.empty()) m_tokens = {};
        GetId();
        try {
            m_tools->Get_m(table_name, m_tokens[0]);
        }
        catch (std::exception& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
        }
    }
    else if (comm == 4) {
        if (!m_tokens.empty()) m_tokens = {};
        GetId();
        GetField();
        try {
            m_tools->Get_s(table_name, m_tokens);
        }
        catch (std::exception& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
        }
    }
    else if (comm == 5) {
        if (!m_tokens.empty()) m_tokens = {};
        GetId();
        try {
            m_tools->Delete(table_name, m_tokens);
        }
        catch (std::exception& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
        }
    }
    else if (comm == 6) {
        try {
            m_tools->GetAll(table_name);
        }
        catch (std::exception& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
        }
    }

    return true;
}
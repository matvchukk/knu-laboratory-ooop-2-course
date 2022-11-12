#pragma once
#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "Structures.h"
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
class Operations {
public:
    Operations();
    bool Add_m(std::string table_name, std::vector<std::string> args);
    void Get_m(std::string table_name, std::string id);
    void Get_s(std::string table_name, std::vector<std::string> fields);
    void GetAll(std::string table_name);
    void Update(std::string table_name, std::vector<std::string> args);
    void Delete(std::string table_name, std::vector<std::string> args);
private:
    std::unique_ptr<Structures> m_db;
};





#endif 

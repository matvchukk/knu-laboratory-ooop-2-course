#pragma once
#ifndef STORAGE_H
#define STORAGE_H

#include <map>
#include <iostream>
#include <memory>
#include <fstream>
template<typename T>
class Storage {
public:
    std::map<int, std::shared_ptr<T>> m_data;
    void Delete(int ID) {
        if (m_data.erase(ID)) {
            std::cout << "Done\n";
        }
        else {
            std::cout << "Doesn't exist\n";
        }
    }
    bool Save(std::shared_ptr<T> element) {
        if (!is_exist(element)) {
            try {
                m_data[element->Get_ID()] = element;
                std::cout << "Done\n" << element->Get_table_name() << " ID: " << element->Get_ID() << std::endl;
            }
            catch (...) {
                std::cerr << "Error\n" << std::endl;
                return false;
            }
            return true;
        }
        else {
            std::cerr << "Element exists" << std::endl;
            return false;
        }
    }

    bool is_exist(std::shared_ptr<T> element) {
        if (m_data.find(element->Get_ID()) == m_data.end()) {
            return false;
        }
        return true;
    }

    std::shared_ptr<T> Get(int ID) {
        if (m_data.find(ID) == m_data.end()) {
            throw std::runtime_error("Doesn't exist");
        }
        else {
            return m_data[ID];
        }
    }

    bool id_exists(int ID) {
        if (m_data.find(ID) == m_data.end()) {
            return false;
        }
        return true;
    }

    std::shared_ptr<T> GetForPrinting(int ID) {
        if (m_data.find(ID) == m_data.end()) {
            GetForPrinting(ID++);
        }
        else {
            return m_data[ID];
        }
    }
};
#endif
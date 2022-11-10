#pragma once

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "Storage.h"
#include "Data.h"
#include <memory>
class Structures {
public:
    Structures();
    std::shared_ptr<Storage<Patient>> GetPatientDb();
    std::shared_ptr<Storage<Card>> GetCardDb();
    std::shared_ptr<Storage<Department>> GetDepartmentDb();
    std::shared_ptr<Storage<Service>> GetServiceDb();
    std::shared_ptr<Storage<Cabinet>> GetCabinetDb();
    std::shared_ptr<Storage<Doctor>> GetDoctorDb();
    ~Structures();
private:
    std::string Parse_stick(std::string& line);
    void Open_file(std::string line);
    std::shared_ptr<Storage<Patient>> patientDb;
    std::shared_ptr<Storage<Card>> cardDb;
    std::shared_ptr<Storage<Department>> departmentDb;
    std::shared_ptr<Storage<Service>> serviceDb;
    std::shared_ptr<Storage<Cabinet>> cabinetDb;
    std::shared_ptr<Storage<Doctor>> doctorDb;
};

#endif
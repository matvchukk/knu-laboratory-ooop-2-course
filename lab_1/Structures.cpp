#include "Structures.h"

Structures::Structures() {
    patientDb = std::make_shared<Storage<Patient>>();
    cardDb = std::make_shared<Storage<Card>>();
    departmentDb = std::make_shared<Storage<Department>>();
    serviceDb = std::make_shared<Storage<Service>>();
    cabinetDb = std::make_shared<Storage<Cabinet>>();
    doctorDb = std::make_shared<Storage<Doctor>>();

    std::string line;
    std::ifstream file("hospital.txt");
    if (file.is_open()) {
        while (file) {
            std::getline(file, line);
            Open_file(line);
        }
    }
}
std::string Structures::Parse_stick(std::string& line) {
    std::string result;
    auto stick_iter = std::find(line.begin(), line.end(), '|');
    if (stick_iter == line.end()) {
        return line;
    }
    else {
        result = std::string(line.begin(), stick_iter);
        line.erase(line.begin(), stick_iter + 1);
    }
    return result;
}
void Structures::Open_file(std::string line) {
    std::string table = Parse_stick(line);
    if (table == "DOCTOR") {
        auto id = Parse_stick(line);
        auto el = std::make_shared<Doctor>(Parse_stick(line), Parse_stick(line), Parse_stick(line), Parse_stick(line), Parse_stick(line), Parse_stick(line)); //LOL WHAT'S THE CODE!!
        if (el->Get_ID() != std::stoi(id)) {
            el->Change_ID(std::stoi(id));
        }
        doctorDb->Save(el);
    }
    else if (table == "PATIENT") {
        auto id = Parse_stick(line);
        auto el = std::make_shared<Patient>(Parse_stick(line), Parse_stick(line), Parse_stick(line), Parse_stick(line), Parse_stick(line), Parse_stick(line)); //LOL WHAT'S THE CODE!!
        if (el->Get_ID() != std::stoi(id)) {
            el->Change_ID(std::stoi(id));
        }
        patientDb->Save(el);
    }
    else if (table == "CABINET") {
        auto id = Parse_stick(line);
        auto el = std::make_shared<Cabinet>(Parse_stick(line), Parse_stick(line), Parse_stick(line)); //LOL WHAT'S THE CODE!!
        if (el->Get_ID() != std::stoi(id)) {
            el->Change_ID(std::stoi(id));
        }
        cabinetDb->Save(el);
    }
    else if (table == "CARD") {
        auto id = Parse_stick(line);
        auto el = std::make_shared<Card>(Parse_stick(line), Parse_stick(line), Parse_stick(line)); //LOL WHAT'S THE CODE!!
        if (el->Get_ID() != std::stoi(id)) {
            el->Change_ID(std::stoi(id));
        }
        cardDb->Save(el);
    }
    else if (table == "DEPARTMENT") {
        auto id = Parse_stick(line);
        auto el = std::make_shared<Department>(Parse_stick(line), Parse_stick(line)); //LOL WHAT'S THE CODE!!
        if (el->Get_ID() != std::stoi(id)) {
            el->Change_ID(std::stoi(id));
        }
        departmentDb->Save(el);
    }
    else if (table == "SERVICE") {
        auto id = Parse_stick(line);
        auto el = std::make_shared<Service>(Parse_stick(line), Parse_stick(line), Parse_stick(line), Parse_stick(line), Parse_stick(line)); //LOL WHAT'S THE CODE!!
        if (el->Get_ID() != std::stoi(id)) {
            el->Change_ID(std::stoi(id));
        }
        serviceDb->Save(el);
    }
}

std::shared_ptr<Storage<Patient>> Structures::GetPatientDb() {
    return patientDb;
}
std::shared_ptr<Storage<Card>> Structures::GetCardDb() {
    return cardDb;
}
std::shared_ptr<Storage<Department>> Structures::GetDepartmentDb() {
    return departmentDb;
}
std::shared_ptr<Storage<Service>> Structures::GetServiceDb() {
    return serviceDb;
}
std::shared_ptr<Storage<Cabinet>> Structures::GetCabinetDb() {
    return cabinetDb;
}
std::shared_ptr<Storage<Doctor>> Structures::GetDoctorDb() {
    return doctorDb;
}

Structures::~Structures() {
    std::ofstream file;
    file.open("hospital.txt");
    if (!file.is_open()) {
        std::cout << "ERROR!";
    }
    if (file.is_open()) {
        for (auto i : doctorDb->m_data) {
            file << "DOCTOR|";
            file << i.second->Get_ID() << "|" << i.second->Get_first_name() << "|" << i.second->Get_last_name() << "|" << i.second->Get_father_name() << "|" <<
                i.second->Get_specialization() << "|" << i.second->Get_experience() << "|" << i.second->Get_category() << "\n";
        }
        for (auto i : patientDb->m_data) {
            file << "PATIENT|";
            file << i.second->Get_ID() << "|" << i.second->Get_first_name() << "|" << i.second->Get_last_name() << "|" << i.second->Get_father_name() << "|" << i.second->Get_phone_number() << "|" << i.second->Get_doctor() << "|" << i.second->Get_card() << "\n";
        }
        for (auto i : cabinetDb->m_data) {
            file << "CABINET|";
            file << i.second->Get_ID() << "|" << i.second->Get_number() << "|" << i.second->Get_floor() << "|" << i.second->Get_equipment() << "\n";
        }
        for (auto i : cardDb->m_data) {
            file << "CARD|";
            file << i.second->Get_ID() << "|" << i.second->Get_service() << "|" << i.second->Get_diagnosis() << "|" << i.second->Get_medical_history() << "\n";
        }
        for (auto i : departmentDb->m_data) {
            file << "DEPARTMENT|";
            file << i.second->Get_ID() << "|" << i.second->Get_name() << "|" << i.second->Get_head() << "\n";
        }
        for (auto i : serviceDb->m_data) {
            file << "SERVICE|";
            file << i.second->Get_ID() << "|" << i.second->Get_cabinet_id() << "|" << i.second->Get_doctor_id() << "|" << i.second->Get_name() << "|" << i.second->Get_date() << "|" << i.second->Get_price() << "\n";
        }
        file.close();
        std::cout << "Saved!\n";
    }
    else {
        std::cout << "Error!\n";
    }
}
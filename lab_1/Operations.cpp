#include <iostream>
#include "Operations.h"

Operations::Operations() {
    m_db.release();
    m_db = std::make_unique<Structures>();
}

bool Operations::Add_m(std::string table_name, std::vector<std::string> args) {
    if (table_name == "DOCTOR") {
        if (args.size() != 6) {
            throw std::runtime_error("Error: Few parameters");
            return false;
        }
        else {
            m_db->GetDoctorDb()->Save(std::make_shared<Doctor>(args[0], args[1], args[2], args[3], args[4], args[5]));
            return true;
        }
    }
    else if (table_name == "PATIENT") {
        if (args.size() != 6) {
            throw std::runtime_error("Error: Few parameters");
            return false;
        }
        else {
            m_db->GetPatientDb()->Save(std::make_shared<Patient>(args[0], args[1], args[2], args[3], args[4], args[5]));
            return true;
        }
    }
    else if (table_name == "CABINET") {
        if (args.size() < 3) {
            throw std::runtime_error("Error: Few parameters");
            return false;
        }
        else {
            std::string descr = "";
            for (int i = 2; i < args.size(); i++) {
                descr += args[i];
                descr += " ";
            }
            descr.pop_back();
            m_db->GetCabinetDb()->Save(std::make_shared<Cabinet>(args[0], args[1], descr));
            return true;
        }
    }
    else if (table_name == "CARD") {
        if (args.size() != 3) {
            throw std::runtime_error("Error: Few parameters");
            return false;
        }
        else {
            m_db->GetCardDb()->Save(std::make_shared<Card>(args[0], args[1], args[2]));
            return true;
        }
    }
    else if (table_name == "PATIENT") {
        if (args.size() != 6) {
            throw std::runtime_error("Error: Few parameters");
            return false;
        }
        else {
            m_db->GetPatientDb()->Save(std::make_shared<Patient>(args[0], args[1], args[2], args[3], args[4], args[5]));
            return true;
        }
    }
    else if (table_name == "DEPARTMENT") {
        if (args.size() != 2) {
            throw std::runtime_error("Error: Few parameters");
            return false;
        }
        else {
            m_db->GetDepartmentDb()->Save(std::make_shared<Department>(args[0], args[1]));
            return true;
        }
    }
    else if (table_name == "SERVICE") {
        if (args.size() != 5) {
            throw std::runtime_error("Error: Few parameters");
            return false;
        }
        else {
            m_db->GetServiceDb()->Save(std::make_shared<Service>(args[0], args[1], args[2], args[3], args[4]));
            return true;
        }
    }
    else {
        throw std::runtime_error("Error: Wrong table");
        return false;
    }
}

void Operations::Get_m(std::string table_name, std::string id) {
    int ID;
    try {
        ID = std::stoi(id);
    }
    catch (...) {
        throw std::runtime_error("Error: Invalid ID");
    }
    if (table_name == "DOCTOR") {
        auto el = m_db->GetDoctorDb()->Get(ID);
        std::cout << "DOCTOR" << el->Get_ID() << "---\n" << "First name:\t" << el->Get_first_name() << "\nLast name:\t" << el->Get_last_name() << "\nFather name:\t" << el->Get_father_name() << "\nSpecialization:\t" << el->Get_specialization() << "\nCategory:\t" << el->Get_category() << "\nExperience:\t" << el->Get_experience() << std::endl;
    }
    else if (table_name == "PATIENT") {
        auto el = m_db->GetPatientDb()->Get(ID);
        std::cout << "PATIENT" << el->Get_ID() << "---\n" << "First name:\t" << el->Get_first_name() << "\nLast name:\t" << el->Get_last_name() << "\nFather name:\t" << el->Get_father_name() << "\nPhone number:\t" << el->Get_phone_number() << "\nMedical card:\t" << el->Get_card() << "\nFamily doctor:\t" << el->Get_doctor() << std::endl;
    }
    else if (table_name == "CABINET") {
        auto el = m_db->GetCabinetDb()->Get(ID);
        std::cout << "CABINET" << el->Get_ID() << "---\n" << "Number:\t" << el->Get_number() << "\nFloor:\t" << el->Get_floor() << "\nEquipment:\t" << el->Get_equipment() << std::endl;
    }
    else if (table_name == "DEPARTMENT") {
        auto el = m_db->GetDepartmentDb()->Get(ID);
        std::cout << "DEPARTMENT" << el->Get_ID() << "---\n" << "Name:\t" << el->Get_name() << "\nHead of department:\t" << el->Get_head() << std::endl;
    }
    else if (table_name == "CARD") {
        auto el = m_db->GetCardDb()->Get(ID);
        std::cout << "CARD" << el->Get_ID() << "---\n" << "Service ID:\t" << el->Get_service() << "\nDiagnosis:\t" << el->Get_diagnosis() << "\nMedical history:\t" << el->Get_medical_history() << std::endl;
    }
    else if (table_name == "SERVICE") {
        auto el = m_db->GetServiceDb()->Get(ID);
        std::cout << "SERVICE" << el->Get_ID() << "---\n" << "Doctor ID:\t" << el->Get_doctor_id() << "\nName:\t" << el->Get_name() << "\nCabinet ID:\t" << el->Get_cabinet_id() << "\nDate:\t" << el->Get_date() << "\nPrice:\t" << el->Get_price() << std::endl;
    }
    else {
        throw std::runtime_error("Error: Wrong table");
    }
}

void Operations::GetAll(std::string table_name) {
    for (size_t i = 1; i < 10; i++) {
        if (table_name == "DOCTOR") {
            if (m_db->GetDoctorDb()->id_exists(i)){
                auto el = m_db->GetDoctorDb()->GetForPrinting(i);
                std::cout << "DOCTOR" << el->Get_ID() << "---\n" << "First name:\t" << el->Get_first_name() << "\nLast name:\t" << el->Get_last_name() << "\nFather name:\t" << el->Get_father_name() << "\nSpecialization:\t" << el->Get_specialization() << "\nCategory:\t" << el->Get_category() << "\nExperience:\t" << el->Get_experience() << std::endl;
            }
        }
        else if (table_name == "PATIENT") {
            if (m_db->GetPatientDb()->id_exists(i)) {
                auto el = m_db->GetPatientDb()->GetForPrinting(i);
                std::cout << "PATIENT" << el->Get_ID() << "---\n" << "First name:\t" << el->Get_first_name() << "\nLast name:\t" << el->Get_last_name() << "\nFather name:\t" << el->Get_father_name() << "\nPhone number:\t" << el->Get_phone_number() << "\nMedical card:\t" << el->Get_card() << "\nFamily doctor:\t" << el->Get_doctor() << std::endl;
            }
        }
        else if (table_name == "CABINET") {
            if (m_db->GetCabinetDb()->id_exists(i)) {
                auto el = m_db->GetCabinetDb()->GetForPrinting(i);
                std::cout << "CABINET" << el->Get_ID() << "---\n" << "Number:\t" << el->Get_number() << "\nFloor:\t" << el->Get_floor() << "\nEquipment:\t" << el->Get_equipment() << std::endl;
            }
        }
        else if (table_name == "DEPARTMENT") {
            if (m_db->GetDepartmentDb()->id_exists(i)) {
                auto el = m_db->GetDepartmentDb()->GetForPrinting(i);
                std::cout << "DEPARTMENT" << el->Get_ID() << "---\n" << "Name:\t" << el->Get_name() << "\nHead of department:\t" << el->Get_head() << std::endl;
            }
        }
        else if (table_name == "CARD") {
            if (m_db->GetCardDb()->id_exists(i)) {
                auto el = m_db->GetCardDb()->GetForPrinting(i);
                std::cout << "CARD" << el->Get_ID() << "---\n" << "Service ID:\t" << el->Get_service() << "\nDiagnosis:\t" << el->Get_diagnosis() << "\nMedical history:\t" << el->Get_medical_history() << std::endl;
            }
        }
        else if (table_name == "SERVICE") {
            if (m_db->GetServiceDb()->id_exists(i)) {
                auto el = m_db->GetServiceDb()->GetForPrinting(i);
                std::cout << "SERVICE" << el->Get_ID() << "---\n" << "Doctor ID:\t" << el->Get_doctor_id() << "\nName:\t" << el->Get_name() << "\nCabinet ID:\t" << el->Get_cabinet_id() << "\nDate:\t" << el->Get_date() << "\nPrice:\t" << el->Get_price() << std::endl;
            }
        }
        else {
            throw std::runtime_error("Error: Wrong table");
            return;
        }
        std::cout << "\n\n";
    }
}

void Operations::Get_s(std::string table_name, std::vector<std::string> fields) {
    std::string ID;
    int id;
    try {
        ID = fields[0];
        id = std::stoi(ID);
        fields.erase(fields.begin());
    }
    catch (...) {
        throw std::runtime_error("Error: Invalid ID");
    }
    if (table_name == "PATIENT") {
        auto el = m_db->GetPatientDb()->Get(id);
        if (fields.size() == 0) {
            std::cout << "Error: put parameter\n";
            std::string allwords;
            std::getline(std::cin, allwords);
            std::string word;
            std::istringstream iss(allwords);
            while (iss >> word) { fields.push_back(word); }
        }
        for (auto field : fields) {
            if (field == "FIRST_NAME") {
                std::cout << el->Get_first_name() << std::endl;
            }
            else if (field == "LAST_NAME") {
                std::cout << el->Get_last_name() << std::endl;
            }
            else if (field == "FATHER_NAME") {
                std::cout << el->Get_father_name() << std::endl;
            }
            else if (field == "PHONE_NUMBER") {
                std::cout << el->Get_phone_number() << std::endl;
            }
            else if (field == "MEDICAL_CARD") {
                std::cout << el->Get_card() << std::endl;
            }
            else if (field == "FAMILY_DOCTOR") {
                std::cout << el->Get_doctor() << std::endl;
            }
            else {
                std::cout << "Error: Wrong parameter " << field << std::endl;
            }
        }
    }
    else if (table_name == "DOCTOR") {
        auto el = m_db->GetDoctorDb()->Get(id);
        if (fields.size() == 0) {
            std::cout << "Error: put parameter\n";
            std::string allwords;
            std::getline(std::cin, allwords);
            std::string word;
            std::istringstream iss(allwords);
            while (iss >> word) { fields.push_back(word); }
        }
        for (auto field : fields) {
            if (field == "FIRST_NAME") {
                std::cout << el->Get_first_name() << std::endl;
            }
            else if (field == "LAST_NAME") {
                std::cout << el->Get_last_name() << std::endl;
            }
            else if (field == "FATHER_NAME") {
                std::cout << el->Get_father_name() << std::endl;
            }
            else if (field == "SPECIALIZATION") {
                std::cout << el->Get_specialization() << std::endl;
            }
            else if (field == "CATEGORY") {
                std::cout << el->Get_category() << std::endl;
            }
            else if (field == "EXPERIENCE") {
                std::cout << el->Get_experience() << std::endl;
            }
            else {
                std::cout << "Error: Wrong parameter" << field << std::endl;
            }
        }
    }
    else if (table_name == "CABINET") {
        auto el = m_db->GetCabinetDb()->Get(id);
        if (fields.size() == 0) {
            std::cout << "Error: put parameter\n";
            std::string allwords;
            std::getline(std::cin, allwords);
            std::string word;
            std::istringstream iss(allwords);
            while (iss >> word) { fields.push_back(word); }
        }
        for (auto field : fields) {
            if (field == "NUMBER") {
                std::cout << el->Get_number() << std::endl;
            }
            else if (field == "FLOOR") {
                std::cout << el->Get_floor() << std::endl;
            }
            else if (field == "EQUIPMENT") {
                std::cout << el->Get_equipment() << std::endl;
            }
            else {
                std::cout << "Error: Wrong parameter" << field << std::endl;
            }
        }
    }
    else if (table_name == "CARD") {
        auto el = m_db->GetCardDb()->Get(id);
        if (fields.size() == 0) {
            std::cout << "Error: put parameter\n";
            std::string allwords;
            std::getline(std::cin, allwords);
            std::string word;
            std::istringstream iss(allwords);
            while (iss >> word) { fields.push_back(word); }
        }
        for (auto field : fields) {
            if (field == "SERVICE") {
                std::cout << el->Get_service() << std::endl;
            }
            else if (field == "DIAGNOSIS") {
                std::cout << el->Get_diagnosis() << std::endl;
            }
            else if (field == "MED_HISTORY") {
                std::cout << el->Get_medical_history() << std::endl;
            }
            else {
                std::cout << "Error: Wrong parameter" << field << std::endl;
            }
        }
    }
    else if (table_name == "DEPARTMENT") {
        if (fields.size() == 0) {
            std::cout << "Error: put parameter\n";
            std::string allwords;
            std::getline(std::cin, allwords);
            std::string word;
            std::istringstream iss(allwords);
            while (iss >> word) { fields.push_back(word); }
        }
        auto el = m_db->GetDepartmentDb()->Get(id);
        for (auto field : fields) {
            if (field == "NAME") {
                std::cout << el->Get_name() << std::endl;
            }
            else if (field == "HEAD") {
                std::cout << el->Get_head() << std::endl;
            }
            else {
                std::cout << "Error: Wrong parameter" << field << std::endl;
            }
        }
    }
    else if (table_name == "SERVICE") {
        if (fields.size() == 0) {
            std::cout << "Error: put parameter\n";
            std::string allwords;
            std::getline(std::cin, allwords);
            std::string word;
            std::istringstream iss(allwords);
            while (iss >> word) { fields.push_back(word); }
        }
        auto el = m_db->GetServiceDb()->Get(id);
        for (auto field : fields) {
            if (field == "DOCTOR") {
                std::cout << el->Get_doctor_id() << std::endl;
            }
            else if (field == "NAME") {
                std::cout << el->Get_name() << std::endl;
            }
            else if (field == "CABINET") {
                std::cout << el->Get_cabinet_id() << std::endl;
            }
            else if (field == "DATE") {
                std::cout << el->Get_date() << std::endl;
            }
            else if (field == "PRICE") {
                std::cout << el->Get_price() << std::endl;
            }

            else {
                std::cout << "Error: Wrong parameter" << field << std::endl;
            }
        }
    }
    else {
        throw std::runtime_error("Error: Wrong table");
    }
}

void Operations::Update(std::string table_name, std::vector<std::string> args) {
    if (args.size() != 3) {
        throw std::logic_error("Error: Few parameters");
    }
    int id;
    try {
        id = std::stoi(args[0]);
    }
    catch (...) {
        throw std::runtime_error("Error: Invalid argument");
    }
    if (table_name == "PATIENT") {
        auto clients_db = m_db->GetPatientDb();
        std::shared_ptr<Patient> el;
        try {
            el = clients_db->Get(id);
        }
        catch (...) {
            throw std::runtime_error("Error: Invalid ID");
        }
        if (args[1] == "FIRST_NAME") {
            try {
                el->Set_first_name(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "LAST_NAME") {
            try {
                el->Set_last_name(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "FATHER_NAME") {
            try {
                el->Set_father_name(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "PHONE_NUMBER") {
            try {
                el->Set_phone_number(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "FAMILY_DOCTOR") {
            try {
                el->Set_doctor(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "MEDICAL_CARD") {
            try {
                el->Set_card(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else {
            throw std::logic_error("Invalid parameters!\n");
        }
        return;
    }
    else if (table_name == "DOCTOR") {
        auto master_db = m_db->GetDoctorDb();
        std::shared_ptr<Doctor> el;
        try {
            el = master_db->Get(id);
        }
        catch (...) {
            throw std::runtime_error("Invalid ID");
        }
        if (args[1] == "FIRST_NAME") {
            try {
                el->Set_first_name(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "LAST_NAME") {
            try {
                el->Set_last_name(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "FATHER_NAME") {
            try {
                el->Set_father_name(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "SPECIALIZATION") {
            try {
                el->Set_specialization(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "EXPERIENCE") {
            try {
                el->Set_experience(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "CATEGORY") {
            try {
                el->Set_category(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else {
            throw std::logic_error("Invalid parameters!\n");
        }
        return;
    }
    else if (table_name == "CABINET") {
        auto device_db = m_db->GetCabinetDb();
        std::shared_ptr<Cabinet> el;
        try {
            el = device_db->Get(id);
        }
        catch (...) {
            throw std::runtime_error("Invalid ID");
        }
        if (args[1] == "NUMBER") {
            try {
                el->Set_number(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "FLOOR") {
            try {
                el->Set_floor(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "EQUIPMENT") {
            try {
                el->Set_equipment(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else {
            throw std::logic_error("Invalid parameters\n");
        }
        return;
    }
    else if (table_name == "DEPARTMENT") {
        auto own_db = m_db->GetDepartmentDb();
        std::shared_ptr<Department> el;
        try {
            el = own_db->Get(id);
        }
        catch (...) {
            throw std::runtime_error("Invalid ID");
        }
        if (args[1] == "NAME") {
            try {
                el->Set_name(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "HEAD") {
            try {
                el->Set_head(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else {
            throw std::logic_error("Invalid parameters!\n");
        }
        return;
    }
    else if (table_name == "CARD") {
        auto service_db = m_db->GetCardDb();
        std::shared_ptr<Card> el;
        try {
            el = service_db->Get(id);
        }
        catch (...) {
            throw std::runtime_error("Invalid ID");
        }
        if (args[1] == "SERVICE") {
            try {
                el->Set_service(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "DIAGNOSIS") {
            try {
                el->Set_diagnosis(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "MED_HISTORY") {
            try {
                el->Set_medical_history(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else {
            throw std::logic_error("Invalid parameters!\n");
        }
        return;
    }
    if (table_name == "SERVICE") {
        auto contract_db = m_db->GetServiceDb();
        std::shared_ptr<Service> el;
        try {
            el = contract_db->Get(id);
        }
        catch (...) {
            throw std::runtime_error("Invalid ID");
        }
        if (args[1] == "NAME") {
            try {
                el->Set_name(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "DOCTOR_ID") {
            try {
                el->Set_doctor_id(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "CABINET_ID") {
            try {
                el->Set_cabinet_id(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "DATE") {
            try {
                el->Set_date(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else if (args[1] == "PRICE") {
            try {
                el->Set_price(args[2]);
                std::cout << "Done!\n";
            }
            catch (...) {
                std::runtime_error("Setting error!");
            }
        }
        else {
            throw std::logic_error("Invalid parameters!\n");
        }
        return;
    }
    else {
        throw std::logic_error("Unknown table!\n DOCTOR/PATIENT/CABINET/DEPARTMENT/SERVICE/CARD\n");
    }
}

void Operations::Delete(std::string table_name, std::vector<std::string> args) {
    int ID;
    try {
        ID = std::stoi(args[0]);
    }
    catch (...) {
        throw std::logic_error("Error: Invalid ID");
    }
    if (table_name == "DOCTOR") {
        try {
            m_db->GetDoctorDb()->Delete(ID);
        }
        catch (...) {
            throw std::runtime_error("Error: Can`t delete");
        }
    }
    else if (table_name == "PATIENT") {
        try {
            if (m_db->GetPatientDb()->id_exists(ID)) {
                auto el = m_db->GetPatientDb()->Get(ID);
                std::cout << "Medical card: ";
                m_db->GetCardDb()->Delete(std::stoi(el->Get_card()));
            }
            m_db->GetPatientDb()->Delete(ID);
        }
        catch (...) {
            throw std::runtime_error("Error: Can`t delete");
        }
    }
    else if (table_name == "CABINET") {
        try {
            m_db->GetCabinetDb()->Delete(ID);
        }
        catch (...) {
            throw std::runtime_error("Error: Can`t delete");
        }
    }
    else if (table_name == "DEPARTMENT") {
        try {
            m_db->GetDepartmentDb()->Delete(ID);
        }
        catch (...) {
            throw std::runtime_error("Error: Can`t delete");
        }
    }
    else if (table_name == "CARD") {
        try {
            m_db->GetCardDb()->Delete(ID);
        }
        catch (...) {
            throw std::runtime_error("Error: Can`t delete");
        }
    }
    else if (table_name == "SERVICE") {
        try {
            m_db->GetServiceDb()->Delete(ID);
        }
        catch (...) {
            throw std::runtime_error("Error: Can`t delete");
        }
    }
    else {
        std::cout << "Error: Wrong table\n";
    }
}
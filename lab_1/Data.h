#pragma once
#ifndef DATA_H
#define DATA_H

#include <string>
#include <map>

class Patient {
private:
    std::string m_last_name;
    std::string m_first_name;
    std::string m_father_name;
    std::string m_phone_number;
    static int Patient_ID;
    int m_id;
    std::string m_family_doctor;
    std::string m_card;
public:
    Patient() {

    }
    Patient(std::string first_name, std::string last_name, std::string father_name, std::string phone_number, std::string family_doctor_last_name, std::string medical_card) : m_last_name(last_name), m_first_name(first_name), m_father_name(father_name), m_phone_number(phone_number), m_family_doctor(family_doctor_last_name), m_card(medical_card) {
        Patient_ID++;
        m_id = Patient_ID;
    }
    std::string Get_last_name() {
        return m_last_name;
    }
    void Set_last_name(std::string last_name) {
        m_last_name = last_name;
    }
    std::string Get_first_name() {
        return m_first_name;
    }
    void Set_first_name(std::string firtst_name) {
        m_first_name = firtst_name;
    }
    std::string Get_father_name() {
        return m_father_name;
    }
    void Set_father_name(std::string father_name) {
        m_father_name = father_name;
    }
    std::string Get_phone_number() {
        return m_phone_number;
    }
    void Set_phone_number(std::string phone) {
        m_phone_number = phone;
    }
    std::string Get_doctor() {
        return m_family_doctor;
    }
    void Change_ID(int new_id) {
        m_id = new_id;
        Patient_ID = new_id;
    }
    void Set_doctor(std::string family_doctor_last_name) {
        m_family_doctor = family_doctor_last_name;
    }
    std::string Get_card() {
        return m_card;
    }
    void Set_card(std::string medical_card) {
        m_card = medical_card;
    }
    int Get_ID() {
        return m_id;
    }
    std::string Get_table_name() {
        return "Patient";
    }
};

class Doctor {
private:
    std::string m_last_name;
    std::string m_first_name;
    std::string m_father_name;
    std::string m_specialization;
    static int Doctor_ID;
    int m_id;
    std::string m_experience;
    std::string m_category;
public:
    Doctor() {

    }
    Doctor(std::string first_name, std::string last_name, std::string father_name, std::string specialization, std::string exp, std::string category) : m_last_name(last_name), m_first_name(first_name), m_experience(exp), m_father_name(father_name), m_specialization(specialization), m_category(category) {
        Doctor_ID++;
        m_id = Doctor_ID;
    }
    void Change_ID(int new_id) {
        m_id = new_id;
        Doctor_ID = new_id;
    }
    std::string Get_last_name() {
        return m_last_name;
    }
    void Set_last_name(std::string last_name) {
        m_last_name = last_name;
    }
    std::string Get_first_name() {
        return m_first_name;
    }
    void Set_first_name(std::string firtst_name) {
        m_first_name = firtst_name;
    }
    std::string Get_father_name() {
        return m_father_name;
    }
    void Set_father_name(std::string father_name) {
        m_father_name = father_name;
    }
    std::string Get_specialization() {
        return m_specialization;
    }
    void Set_specialization(std::string specialization) {
        m_specialization = specialization;
    }
    std::string Get_experience() {
        return m_experience;
    }
    void Set_experience(std::string exp) {
        m_experience = exp;
    }
    std::string Get_category() {
        return m_category;
    }
    void Set_category(std::string category) {
        m_category = category;
    }
    int Get_ID() {
        return m_id;
    }
    std::string Get_table_name() {
        return "Doctor";
    }
};

class Cabinet {
    static int Cabinet_ID;
    int m_id;
    std::string m_number;
    std::string m_floor;
    std::string m_equipment;
public:
    Cabinet() {

    }
    Cabinet(std::string number, std::string floor, std::string equipment) : m_number(number), m_floor(floor), m_equipment(equipment) {
        Cabinet_ID++;
        m_id = Cabinet_ID;
    }
    std::string Get_number() {
        return m_number;
    }
    void Change_ID(int new_id) {
        m_id = new_id;
        Cabinet_ID = new_id;
    }
    void Set_number(std::string number) {
        m_number = number;
    }
    std::string Get_floor() {
        return m_floor;
    }
    void Set_floor(std::string floor) {
        m_floor = floor;
    }
    std::string Get_equipment() {
        return m_equipment;
    }
    void Set_equipment(std::string equipment) {
        m_equipment = equipment;
    }
    int Get_ID() {
        return m_id;
    }
    std::string Get_table_name() {
        return "Cabinet";
    }
};

class Card {
private:
    std::string m_service_id;
    std::string m_diagnosis;
    std::string m_medical_history;
    static int Card_ID;
    int m_id;
public:
    Card() {
    }
    void Change_ID(int new_id) {
        m_id = new_id;
        Card_ID = new_id;
    }
    Card(std::string service_id, std::string diagnosis, std::string medical_history) : m_service_id(service_id), m_diagnosis(diagnosis), m_medical_history(medical_history) {
        Card_ID++;
        m_id = Card_ID;
    }
    std::string Get_service() {
        return m_service_id;
    }
    void Set_service(std::string service) {
        m_service_id = service;
    }
    std::string Get_diagnosis() {
        return m_diagnosis;
    }
    void Set_diagnosis(std::string diagnosis) {
        m_diagnosis = diagnosis;
    }
    std::string Get_medical_history() {
        return m_medical_history;
    }
    void Set_medical_history(std::string medical_history) {
        m_medical_history = medical_history;
    }
    int Get_ID() {
        return m_id;
    }
    std::string Get_table_name() {
        return "Card";
    }

};

class Department {
    static int Department_ID;
    int m_id;
    std::string m_name;
    std::string m_head_of_department;
public:
    Department() {

    }
    void Change_ID(int new_id) {
        m_id = new_id;
        Department_ID = new_id;
    }
    Department(std::string name, std::string head) : m_name(name), m_head_of_department(head) {
        Department_ID++;
        m_id = Department_ID;
    }
    std::string Get_name() {
        return m_name;
    }
    void Set_name(std::string name) {
        m_name = name;
    }
    std::string Get_head() {
        return m_head_of_department;
    }
    void Set_head(std::string head) {
        m_head_of_department = head;
    }
    int Get_ID() {
        return m_id;
    }
    std::string Get_table_name() {
        return "Department";
    }
};

class Service {
    static int Service_ID;
    int m_id;
    std::string m_cabinet_id;
    std::string m_doctor_id;
    std::string m_name;
    std::string m_date;
    std::string m_price;

public:
    Service() {

    }
    void Change_ID(int new_id) {
        m_id = new_id;
        Service_ID = new_id;
    }
    Service(std::string cabinet_id, std::string doctor_id, std::string name, std::string date, std::string price) : m_cabinet_id(cabinet_id), m_doctor_id(doctor_id), m_name(name), m_date(date), m_price(price) {
        Service_ID++;
        m_id = Service_ID;
    }
    std::string Get_cabinet_id() {
        return m_cabinet_id;
    }
    void Set_cabinet_id(std::string cabinet) {
        m_cabinet_id = cabinet;
    }
    std::string Get_doctor_id() {
        return m_doctor_id;
    }
    void Set_doctor_id(std::string doctor) {
        m_doctor_id = doctor;
    }
    std::string Get_name() {
        return m_name;
    }
    void Set_name(std::string name) {
        m_name = name;
    }
    int Get_ID() {
        return m_id;
    }
    std::string Get_date() {
        return m_date;
    }
    void Set_date(std::string date) {
        m_date = date;
    }
    std::string Get_price() {
        return m_price;
    }
    void Set_price(std::string price) {
        m_price = price;
    }

    std::string Get_table_name() {
        return "Service";
    }
};
#endif
#include <iostream>
#include "provider.h"

Provider::Provider(std::string name, std::string phone, std::string address){
    this->id = -1;
    this->name = name;
    this->phone = phone;
    this->address = address;
}

void Provider::display(){
    std::cout << "Id: " << this->id << std::endl;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Phone: " << this->phone << std::endl;
    std::cout << "Address: " << this->address << std::endl;
}

void Provider::scan(){
    std::cout << "Provider ID: " << std::endl;
    std::cin >> this->id;
    std::cout << "Provider Name: " << std::endl;
    std::cin >> this->name;
    std::cout << "Provider Phone: " << std::endl;
    std::cin >> this->phone;
    std::cout << "Provider Address: " << std::endl;
    std::cin >> this->address;
}

long Provider::getId(){
    return this->id;
}

std::string Provider::getName(){
    return this->name;
}

std::string Provider::getPhone(){
    return this->phone;
}

std::string Provider::getAddress(){
    return this->address;
}

void Provider::setId(long id){
    this->id = id;
}

void Provider::setName(std::string name){
    this->name = name;
}

void Provider::setPhone(std::string phone){
    this->phone = phone;
}

void Provider::setAddress(std::string address){
    this->address = address;
}


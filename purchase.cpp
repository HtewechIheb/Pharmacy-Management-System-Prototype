#include <iostream>
#include <cctype>
#include <ctime>
#include <algorithm>
#include "general.h"
#include "Purchase.h"


Purchase::Purchase(std::list<Medicine> medicines, double total, std::time_t date){
    this->medicines = medicines;
    this->total = total;
    this->date = date;
}

void Purchase::display(){
    std::cout << "Purchase ID: " << this->id << std::endl;
    std::cout << "Purchase medicines: " << std::endl << std::endl;
    for(std::list<Medicine>::iterator iter = this->medicines.begin(); iter != this->medicines.end(); iter++){
        iter->display();
        std::cout << std::endl;
    }
    std::cout << "Purchase total: " << this->total << std::endl;
    std::cout << "Purchase date: " << this->getDateAsString() << std::endl;
}

void Purchase::scan(Medicines& medicinesList){
    std::string answer;
    Medicine* medicine;
    std::tm currentDate = {};
    std::tm buffer;
    std::time_t currentDateTime;

    medicinesList.display();
    std::cout << "Purchase medicines (Select ID): ";
    do{
        do{
            std::cin >> answer;
            medicine = medicinesList.findById(std::stol(answer, nullptr, 10));
        }
        while(medicine == nullptr);
        this->medicines.push_back(*medicine);
        medicinesList.remove(std::stol(answer, nullptr, 10));
        std::cout << "Add another medicine ? (Y/N): ";
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer == "y");

    this->total = 0;
    for(std::list<Medicine>::iterator iter = this->medicines.begin(); iter != this->medicines.end(); iter++){
        total += iter->getPrice();
    }

    currentDateTime = std::time(NULL);
    buffer = *std::localtime(&currentDateTime);
    currentDate.tm_mday = buffer.tm_mday;
    currentDate.tm_mon = buffer.tm_mon;
    currentDate.tm_year = buffer.tm_year;
    this->date = std::mktime(&currentDate);
}

void Purchase::addMedicine(Medicine medicine){
    this->medicines.push_back(medicine);
}

void Purchase::clearMedicines(){
    this->medicines.clear();
}

long Purchase::getId(){
    return this->id;
}

std::list<Medicine> Purchase::getMedicines(){
    return this->medicines;
}

double Purchase::getTotal(){
    return this->total;
}

std::time_t Purchase::getDate(){
    return this->date;
}

std::tm Purchase::getDateAsStruct(){
    return *std::localtime(&this->date);
};

std::string Purchase::getDateAsString(){
    char dateString[100];
    std::strftime(dateString, sizeof(dateString), "%d/%m/%Y", localtime(&this->date));
    return dateString;
};

void Purchase::setId(long id){
    this->id = id;
}

void Purchase::setMedicines(std::list<Medicine> medicines){
    this->medicines = medicines;
}

void Purchase::setTotal(double total){
    this->total = total;
}

void Purchase::setDate(std::time_t date){
    this->date = date;
}


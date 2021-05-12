#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "medicine.h"
#include "medicines.h"
#include "general.h"

Medicines::Medicines(std::list<Medicine> medicines){
    this->medicines = medicines;
}

void Medicines::display(){
    std::cout << "======== All Medicines ========" << std::endl;
    for(std::list<Medicine>::iterator iter = this->medicines.begin(); iter != this->medicines.end(); iter++){
        iter->display();
        std::cout << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

void Medicines::add(){
    Medicine medicine;
    medicine.scan();
    this->medicines.push_back(medicine);
    std::cout << "  Medicine successfully added!" << std::endl;
}

void Medicines::search(){
    MedicineEnumMaps medicineEnumMaps;
    std::string answer;
    Medicine searchedMedicine;

    std::cout << "  Search by ID ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Medicine ID: ";
        std::cin >> answer;
        searchedMedicine.setId(std::stol(answer, nullptr, 10));
    }
    else{
        searchedMedicine.setId(-1);
    }

    std::cout << "  Search by name ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Medicine name: ";
        std::cin >> answer;
        searchedMedicine.setName(answer);
    }
    else{
        searchedMedicine.setName("");
    }

    std::cout << "  Search by type ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Medicine type: "  << std::endl;
        searchedMedicine.setType(enumScan<Type>(medicineEnumMaps.getTypeMap()));
    }
    else{
        searchedMedicine.setType(Type::NONE);
    }

    std::cout << "  Search by category ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Medicine category: "  << std::endl;
        searchedMedicine.setCategory(enumScan<Category>(medicineEnumMaps.getCategoryMap()));
    }
    else{
        searchedMedicine.setCategory(Category::NONE);
    }

    std::cout << "  Search by price ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Medicine price: ";
        std::cin >> answer;
        searchedMedicine.setPrice(std::stoi(answer, nullptr, 10));
    }
    else{
        searchedMedicine.setPrice(-1);
    }

    std::cout << "  Search by creation date ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Medicine creation date: " << std::endl;
        searchedMedicine.setCreationDate(dateScan());
    }
    else{
        searchedMedicine.setCreationDate(static_cast<time_t>(-1));
    }

    std::cout << "  Search by consumption delay ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Medicine consumption delay: " << std::endl;
        std::cin >> answer;
        searchedMedicine.setConsumptionDelay(dateScan());
    }
    else{
        searchedMedicine.setConsumptionDelay(static_cast<time_t>(-1));
    }

    std::list<Medicine> result;
    std::list<Medicine>::iterator iter = this->medicines.begin();
    std::list<Medicine>::iterator last = this->medicines.end();

    while((iter = std::find_if(iter, last,
        [&searchedMedicine](Medicine medicine){
            return (searchedMedicine.getId() == -1 || searchedMedicine.getId() == medicine.getId())
                    && (searchedMedicine.getName() == "" || str_tolower(searchedMedicine.getName()) == str_tolower(medicine.getName()))
                    && (searchedMedicine.getType() == Type::NONE || searchedMedicine.getType() == medicine.getType())
                    && (searchedMedicine.getCategory() == Category::NONE || searchedMedicine.getCategory() == medicine.getCategory())
                    && (searchedMedicine.getPrice() == -1 || searchedMedicine.getPrice() == medicine.getPrice())
                    && (searchedMedicine.getCreationDate() == static_cast<time_t>(-1) || searchedMedicine.getCreationDate() == medicine.getCreationDate())
                    && (searchedMedicine.getConsumptionDelay() == static_cast<time_t>(-1) || searchedMedicine.getConsumptionDelay() == medicine.getConsumptionDelay());
        })) != last)
    {
        result.push_back(*iter);
        iter++;
    }

    std::cout << "======== Search Results ========" << std::endl;
    for(std::list<Medicine>::iterator iter = result.begin(); iter != result.end(); iter++){
        iter->display();
        std::cout << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

void Medicines::edit(){
    Medicine medicine;
    std::list<Medicine>::iterator iter;

    medicine.scan();

    iter = std::find_if(this->medicines.begin(), this->medicines.end(),
        [&medicine](Medicine currentMedicine){
            return currentMedicine.getId() == medicine.getId();
        }
    );

    if(iter == this->medicines.end()){
        std::cout << "  Medicine does not exist!" << std::endl;
    }

    *iter = medicine;
    std::cout << "  Medicine successfully modified!" << std::endl;
}

void Medicines::remove(){
    long id;

    std::cout << "  Medicine ID: ";
    std::cin >> id;

    this->medicines.remove_if(
        [id](Medicine currentMedicine){
            return currentMedicine.getId() == id;
        }
    );

    std::cout << "  Medicine successfully deleted!" << std::endl;
}

Medicine* Medicines::findByName(std::string name){
    std::list<Medicine>::iterator iter;
    iter = std::find_if(this->medicines.begin(), this->medicines.end(), [name](Medicine medicine) {return str_tolower(medicine.getName()) == str_tolower(name);});
    if(iter != this->medicines.end()){
        return &(*iter);
    }
    return nullptr;
}

void Medicines::readFromFile(){
    std::ifstream file;
    file.open("medicines.bin", std::ifstream::in | std::ifstream::binary);

    if(file.is_open()){
        boost::archive::text_iarchive inputArchive(file);
        inputArchive >> this->medicines;
    }
}

void Medicines::writeToFile(){
    std::ofstream file;
    file.open("medicines.bin", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    if(file.is_open()){
        boost::archive::text_oarchive outputArchive(file);
        outputArchive << this->medicines;
    }
}


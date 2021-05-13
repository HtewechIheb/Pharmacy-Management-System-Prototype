#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "general.h"
#include "purchases.h"

Purchases::Purchases(std::list<Purchase> purchases){
    this->purchases = purchases;
}

void Purchases::display(){
    std::cout << "======== All Purchases ========" << std::endl << std::endl;
    for(std::list<Purchase>::iterator iter = this->purchases.begin(); iter != this->purchases.end(); iter++){
        iter->display();
        std::cout << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

void Purchases::add(Medicines& medicinesList){
    Purchase purchase;
    purchase.scan(medicinesList);
    purchase.setId(this->generateId());
    this->purchases.push_back(purchase);
    std::cout << "Purchase successfully added!" << std::endl;
}

void Purchases::search(){
    std::string answer;
    long id;
    std::string medicineName;
    double total;
    std::time_t date;

    std::cout << "Search by ID ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Purchase ID: ";
        std::cin >> answer;
        id = std::stol(answer, nullptr, 10);
    }
    else{
        id = -1;
    }

    std::cout << "Search by medicine ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Medicine name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, answer);
        medicineName = answer;
    }
    else{
        medicineName = "";
    }

    std::cout << "Search by total ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Purchase total: ";
        std::cin >> answer;
        total = std::stod(answer, nullptr);
    }
    else{
        total = -1;
    }

    std::cout << "Search by date ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Purchase address: ";
        date = dateScan();
    }
    else{
        date = static_cast<std::time_t>(-1);
    }

    std::list<Purchase> result;
    std::list<Purchase>::iterator iter = this->purchases.begin();
    std::list<Purchase>::iterator last = this->purchases.end();


    while((iter = std::find_if(iter, last,
        [=](Purchase purchase){
            std::list<Medicine> purchaseMedicines;

            purchaseMedicines = purchase.getMedicines();
            return (id == -1 || id == purchase.getId())
                    && (medicineName == "" || std::find_if(purchaseMedicines.begin(), purchaseMedicines.end(),
                            [&](Medicine medicine) {
                                return str_tolower(medicineName) == str_tolower(medicine.getName());
                            }
                        ) != purchaseMedicines.end())
                    && (total == -1 || total == purchase.getTotal())
                    && (date == static_cast<std::time_t>(-1) || date == purchase.getDate());
        })) != last)
    {
        result.push_back(*iter);
        iter++;
    }

    std::cout << "======== Search Results ========" << std::endl << std::endl;
    for(std::list<Purchase>::iterator iter = result.begin(); iter != result.end(); iter++){
        iter->display();
        std::cout << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

void Purchases::edit(Medicines& medicinesList){
    long id;
    std::string answer;
    std::list<Purchase>::iterator iter;
    std::list<Medicine> purchaseMedicines;
    Medicine* medicine;
    double total;

    this->display();
    std::cout << "Purchase ID: ";
    std::cin >> id;

    iter = std::find_if(this->purchases.begin(), this->purchases.end(),
        [&](Purchase purchase) {
            return id == purchase.getId();
        }
    );

    if(iter == this->purchases.end()){
        std::cout << "Purchase does not exist!" << std::endl;
    }
    else{
        purchaseMedicines = iter->getMedicines();
        for(std::list<Medicine>::iterator medIter = purchaseMedicines.begin(); medIter != purchaseMedicines.end(); medIter++){
            medicinesList.add(*medIter);
        }
        iter->clearMedicines();

        medicinesList.display();
        std::cout << "Purchase medicines (Select ID): " << std::endl;
        do{
            do{
                std::cin >> answer;
                medicine = medicinesList.findById(std::stol(answer, nullptr, 10));
            }
            while(medicine == nullptr);
            iter->addMedicine(*medicine);
            medicinesList.remove(std::stoi(answer, nullptr, 10));
            std::cout << "Add another medicine ? (Y/N): ";
            std::cin >> answer;
            answer = str_tolower(answer);
        }
        while(answer == "y");

        total = 0;
        for(std::list<Medicine>::iterator medIter = purchaseMedicines.begin(); medIter != purchaseMedicines.end(); medIter++){
            total += medIter->getPrice();
        }
        iter->setTotal(total);

        std::cout << "Purchase successfully modified!" << std::endl;
    }
}

void Purchases::remove(Medicines& medicinesList){
    long id;
    std::string answer;
    std::list<Purchase>::iterator iter;
    std::list<Medicine> purchaseMedicines;

    this->display();
    std::cout << "Purchase ID: ";
    std::cin >> id;
    iter = std::find_if(this->purchases.begin(), this->purchases.end(),
        [&](Purchase purchase) {
            return id == purchase.getId();
        }
    );

    if(iter == this->purchases.end()){
        std::cout << "Purchase does not exist!" << std::endl;
    }
    else{
        purchaseMedicines = iter->getMedicines();
        do{
            std::cout << "Return medicines to storage ? (Y/N):";
            std::cin >> answer;
            answer = str_tolower(answer);
        }
        while(answer != "y" && answer != "n");
        if(answer == "y"){
            for(std::list<Medicine>::iterator medIter = purchaseMedicines.begin(); medIter != purchaseMedicines.end(); medIter++){
                medicinesList.add(*medIter);
            }
        }

        this->purchases.erase(iter);

        std::cout << "Purchase successfully deleted!" << std::endl;
    }
}

long Purchases::generateId(){
    long id = 0;
    for(std::list<Purchase>::iterator iter = this->purchases.begin(); iter != this->purchases.end(); iter++){
        if(iter->getId() > id){
            id = iter->getId();
        }
    }

    return id + 1;
}

void Purchases::readFromFile(){
    std::ifstream file;
    file.open("purchases.bin", std::ifstream::in | std::ifstream::binary);

    if(file.is_open()){
        boost::archive::text_iarchive inputArchive(file);
        inputArchive >> this->purchases;
    }
}

void Purchases::writeToFile(){
    std::ofstream file;
    file.open("purchases.bin", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    if(file.is_open()){
        boost::archive::text_oarchive outputArchive(file);
        outputArchive << this->purchases;
    }
}

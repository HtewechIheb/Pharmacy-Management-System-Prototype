#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "general.h"
#include "providerOrders.h"

ProviderOrders::ProviderOrders(std::list<ProviderOrder> providerOrders){
    this->providerOrders = providerOrders;
}

void ProviderOrders::display(){
    std::cout << "======== All Provider Orders ========" << std::endl;
    for(std::list<ProviderOrder>::iterator iter = this->providerOrders.begin(); iter != this->providerOrders.end(); iter++){
        iter->display();
        std::cout << std::endl;
    }
    std::cout << "-------------------------------------" << std::endl;
}

void ProviderOrders::deliver(Medicines& medicinesList){
    long id;
    std::list<ProviderOrder>::iterator providerOrder;

    std::cout << "  Order ID: ";
    do{
        std::cin >> id;
        providerOrder = std::find_if(this->providerOrders.begin(), this->providerOrders.end(),
            [&](ProviderOrder currentProviderOrder) {
                return currentProviderOrder.getId() == id;
            }
        );
    }
    while(providerOrder == this->providerOrders.end());

    providerOrder->deliver(medicinesList);
}

void ProviderOrders::add(Providers providersList){
    ProviderOrder providerOrder;
    providerOrder.scan(providersList);
    providerOrder.setId(this->generateId());
    this->providerOrders.push_back(providerOrder);
    std::cout << "  Provider order successfully added!" << std::endl;
}

void ProviderOrders::search(Providers providersList){
    std::string answer;
    long id;
    std::string medicineName;
    long providerId;
    int delivered;

    std::cout << "  Search by ID ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Provider order ID: ";
        std::cin >> answer;
        id = std::stol(answer, nullptr, 10);
    }
    else{
        id = -1;
    }

    std::cout << "  Search by medicine ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Medicine name: ";
        std::cin >> answer;
        medicineName = answer;
    }
    else{
        medicineName = "";
    }

    std::cout << "  Search by delivery status ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Delivery status: " << std::endl;
        std::cout << "      Delivered: 1" << std::endl;
        std::cout << "      Not Delivered: 2" << std::endl;
        std::cin >> answer;
        if(answer == "1"){
            delivered = 1;
        }
        else if(answer == "2"){
            delivered = 0;
        }
        else {
            delivered = -1;
        }
    }
    else{
        delivered = -1;
    }

    std::cout << "  Search by provider ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Provider (Select ID): "<< std::endl;
        providersList.display();
        do{
            std::cin >> providerId;
        }
        while(providersList.findById(providerId) == nullptr);
    }
    else{
        providerId = -1;
    }

    std::list<ProviderOrder> result;
    std::list<ProviderOrder>::iterator iter = this->providerOrders.begin();
    std::list<ProviderOrder>::iterator last = this->providerOrders.end();

    while((iter = std::find_if(iter, last,
        [&](ProviderOrder providerOrder){
            std::map<std::string, int> providerOrderMedicines;

            providerOrderMedicines = providerOrder.getMedicines();
            return (id == -1 || id == providerOrder.getId())
                    && (medicineName == "" || std::find_if(providerOrderMedicines.begin(), providerOrderMedicines.end(),
                            [&](std::pair<std::string, int> medicineEntry) {
                                return str_tolower(medicineName) == str_tolower(medicineEntry.first);
                            }
                        ) != providerOrderMedicines.end())
                    && (providerId == -1 || providerId == providerOrder.getProvider().getId())
                    && (delivered == -1 || static_cast<bool>(delivered) == providerOrder.getDelivered());
        })) != last)
    {
        result.push_back(*iter);
        iter++;
    }

    std::cout << "======== Search Results ========" << std::endl;
    for(std::list<ProviderOrder>::iterator iter = result.begin(); iter != result.end(); iter++){
        iter->display();
        std::cout << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

void ProviderOrders::edit(Providers providersList){
    ProviderOrder providerOrder;
    std::list<ProviderOrder>::iterator iter;

    providerOrder.scan(providersList);

    iter = std::find_if(this->providerOrders.begin(), this->providerOrders.end(),
        [&](ProviderOrder currentProviderOrder){
            return currentProviderOrder.getId() == providerOrder.getId();
        }
    );

    if(iter == this->providerOrders.end()){
        std::cout << "  Provider order does not exist!" << std::endl;
    }
    else{
        *iter = providerOrder;
        std::cout << "  Provider order successfully modified!" << std::endl;
    }
}

void ProviderOrders::remove(){
    long id;
    std::list<ProviderOrder>::iterator iter;

    std::cout << "  Provider order ID: ";
    std::cin >> id;

    iter = std::find_if(this->providerOrders.begin(), this->providerOrders.end(),
        [&](ProviderOrder currentProviderOrder){
            return currentProviderOrder.getId() == id;
        }
    );

    if(iter == this->providerOrders.end()){
        std::cout << "  Provider order does not exist!" << std::endl;
    }
    else{
        this->providerOrders.erase(iter);

        std::cout << "  Provider order successfully deleted!" << std::endl;
    }
}

long ProviderOrders::generateId(){
    long id = 0;
    for(std::list<ProviderOrder>::iterator iter = this->providerOrders.begin(); iter != this->providerOrders.end(); iter++){
        if(iter->getId() > id){
            id = iter->getId();
        }
    }

    return id + 1;
}

void ProviderOrders::removeByProvider(long providerId){
    this->providerOrders.remove_if(
        [&](ProviderOrder providerOrder){
            return providerOrder.getProvider().getId() == providerId;
        }
    );
}

void ProviderOrders::readFromFile(){
    std::ifstream file;
    file.open("provider_orders.bin", std::ifstream::in | std::ifstream::binary);

    if(file.is_open()){
        boost::archive::text_iarchive inputArchive(file);
        inputArchive >> this->providerOrders;
    }
}

void ProviderOrders::writeToFile(){
    std::ofstream file;
    file.open("provider_orders.bin", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    if(file.is_open()){
        boost::archive::text_oarchive outputArchive(file);
        outputArchive << this->providerOrders;
    }
}




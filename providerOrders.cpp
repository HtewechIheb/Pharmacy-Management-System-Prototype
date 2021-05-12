#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "providerOrder.h"
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

void ProviderOrders::add(Providers providers, Medicines medicinesList){
    ProviderOrder providerOrder;
    providerOrder.scan(providers, medicinesList);
    this->providerOrders.push_back(providerOrder);
    std::cout << "  Provider order successfully added!" << std::endl;
}

void ProviderOrders::search(Providers providers){
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
        providers.display();
        do{
            std::cin >> providerId;
        }
        while(providers.findById(providerId) == nullptr);
    }
    else{
        providerId = -1;
    }

    std::list<ProviderOrder> result;
    std::list<ProviderOrder>::iterator iter = this->providerOrders.begin();
    std::list<ProviderOrder>::iterator last = this->providerOrders.end();

    while((iter = std::find_if(iter, last,
        [&](ProviderOrder providerOrder){
            return (id == -1 || id == providerOrder.getId())
                    && (medicineName == "" || std::find_if(providerOrder.getMedicines().begin(), providerOrder.getMedicines().end(), [&](std::pair<std::string, int> medicineEntry) { return str_tolower(medicineName) == str_tolower(medicineEntry.first); }) != providerOrder.getMedicines().end())
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

void ProviderOrders::edit(Providers providers, Medicines medicinesList){
    ProviderOrder providerOrder;
    std::list<ProviderOrder>::iterator iter;

    providerOrder.scan(providers, medicinesList);

    iter = std::find_if(this->providerOrders.begin(), this->providerOrders.end(),
        [&providerOrder](ProviderOrder currentProviderOrder){
            return currentProviderOrder.getId() == providerOrder.getId();
        }
    );

    if(iter == this->providerOrders.end()){
        std::cout << "  Provider order does not exist!" << std::endl;
    }

    *iter = providerOrder;
    std::cout << "  Provider order successfully modified!" << std::endl;
}

void ProviderOrders::remove(){
    long id;

    std::cout << "  Provider order ID: ";
    std::cin >> id;

    this->providerOrders.remove_if(
        [id](ProviderOrder currentProviderOrder){
            return currentProviderOrder.getId() == id;
        }
    );

    std::cout << "  Provider order successfully deleted!" << std::endl;
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




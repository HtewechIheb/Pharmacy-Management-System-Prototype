#include <iostream>
#include "providerOrder.h"

ProviderOrder::ProviderOrder(Provider provider, std::map<std::string, int> medicines, bool delivered){
    this->provider = provider;
    this->medicines = medicines;
    this->delivered = delivered;
}

void ProviderOrder::display(){
    std::cout << "  Order ID: " << this->id << std::endl;
    std::cout << "  Medicines: " << std::endl;
    for(std::map<std::string, int>::iterator iter = this->medicines.begin(); iter != this->medicines.end(); iter++){
        std::cout << "      " << iter->first << ": " << iter->second << std::endl;
    }
    std::cout << "  Delivery Status: " << (this->delivered ? "Delivered" : "Not Delivered") << std::endl;
    std::cout << "  Provider: " << std::endl;
    this->provider.display();

}

void ProviderOrder::scan(Providers providers){
    long providerId;
    Provider* provider;
    std::string answer;
    std::pair<std::string, int> medicineEntry;

    std::cout << "  Order ID: ";
    std::cin >> this->id;

    std::cout << "  Medicines: ";
    do{
        std::cout << "      Medicine Name: ";
        std::cin >> medicineEntry.first;
        std::cout << "      Quantity: ";
        std::cin >> medicineEntry.second;
        this->medicines.insert(this->medicines.end(), medicineEntry);

        std::cout << "  Add another medicine (Y/N) ?";
        std::cin >> answer;
    }
    while(str_tolower(answer) != "n");

    this->delivered = false;

    std::cout << "  Provider (Select ID): "<< std::endl;
    providers.display();
    do{
        std::cin >> providerId;
        provider = providers.findById(providerId);
    }
    while(provider == nullptr);
    this->provider = *provider;
}

void ProviderOrder::deliver(Medicines& medicinesList){
    Medicine medicine;

    if(this->delivered){
        return;
    }

    for(std::map<std::string, int>::iterator iter = this->medicines.begin(); iter != this->medicines.end(); iter++){
        medicine.setName(iter->first);
        medicine.deliveryScan();
        for(int i = 0; i < iter->second; i++){
            medicine.setId(medicinesList.generateId());
            medicinesList.add(medicine);
        }
    }

    this->delivered = true;
}

long ProviderOrder::getId(){
    return this->id;
}

Provider ProviderOrder::getProvider(){
    return this->provider;
}

std::map<std::string, int> ProviderOrder::getMedicines(){
    return this->medicines;
}

bool ProviderOrder::getDelivered(){
    return this->delivered;
}

void ProviderOrder::setId(long id){
    this->id = id;
}

void ProviderOrder::setProvider(Provider provider){
    this->provider = provider;
}

void ProviderOrder::setMedicines(std::map<std::string, int> medicines){
    this->medicines = medicines;
}

void ProviderOrder::setDelivered(bool delivered){
    this->delivered = delivered;
}


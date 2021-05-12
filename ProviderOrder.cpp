#include "providerOrder.h"
#include "general.h"

ProviderOrder::ProviderOrder(Provider provider, std::map<string, int> medicines, bool delivered){
    this->provider = provider;
    this->medicines = medicines;
    this->delivered = delivered;
}

void ProviderOrder::display(){
    std::cout << "  Order ID: " << this->id << std::endl;
    std::cout << "  Medicines: " << std::endl;
    for(std::map<string, int>::iterator iter = this->medicines.begin(); iter != this->medicines.end(); i++){
        std::cout << "      " << iter->first << ": " << iter->second << std::endl;
    }
    std::cout << "  Delivery Status: " << (this->delivered ? "true" : "false") << std::endl;
    std::cout << "  Provider: " << << std::endl;
    std::cout << this->provider.display() << std::endl;

}

void ProviderOrder::scan(Providers providers, Medicines medicines){
    long providerId;
    Provider* provider;
    std::string answer;

    std::cout << "  Order ID: ";
    std::cin >> this->id;
    std::cout << "  Medicines: ";
    do{
        do{
            std::cout << "      Medicine Name: ";
            std::cin >> answer;
        }
        while()
    }
    while(str_tolower(answer) != "n")

    std::cin >> this->medicineName;
    std::cout << "  Quantity: ";
    std::cin >> this->quantity;
    this->delivered = false;
    std::cout << "  Provider (Select ID): "<< std::endl;
    providers.display();
    do{
        std::cin >> providerId;
        provider = providers.find(providerId);
    }
    while(provider == nullptr);
    this->provider = *provider;
}

long ProviderOrder::getId(){
    return this->id;
}

Provider ProviderOrder::getProvider(){
    return this->provider;
}

std::string ProviderOrder::getMedicineName(){
    return this->medicineName;
}

std::string ProviderOrder::getQuantity(){
    return this->quantity;
}

std::string ProviderOrder::getDelivered(){
    return this->delivered;
}

void ProviderOrder::setId(long id){
    this->id = id;
}

void ProviderOrder::setProvider(Provider provider){
    this->provider = provider;
}

void ProviderOrder::setMedicineName(std::string medicineName){
    this->medicineName = medicineName;
}

void ProviderOrder::setQuantity(std::string quantity){
    this->quantity = quantity;
}

void ProviderOrder::setDelivered(std::string delivered){
    this->delivered = delivered;
}


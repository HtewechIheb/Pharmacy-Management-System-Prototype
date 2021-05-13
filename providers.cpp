#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "general.h"
#include "providers.h"

Providers::Providers(std::list<Provider> providers){
    this->providers = providers;
}

void Providers::display(){
    std::cout << "======== All Providers ========" << std::endl << std::endl;
    for(std::list<Provider>::iterator iter = this->providers.begin(); iter != this->providers.end(); iter++){
        iter->display();
        std::cout << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

void Providers::add(){
    Provider provider;
    provider.scan();
    provider.setId(this->generateId());
    this->providers.push_back(provider);
    std::cout << "Provider successfully added!" << std::endl;
}

void Providers::search(){
    std::string answer;
    Provider searchedProvider;

    std::cout << "Search by ID ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Provider ID: ";
        std::cin >> answer;
        searchedProvider.setId(std::stol(answer, nullptr, 10));
    }
    else{
        searchedProvider.setId(-1);
    }

    std::cout << "Search by name ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Provider name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, answer);
        searchedProvider.setName(answer);
    }
    else{
        searchedProvider.setName("");
    }

    std::cout << "Search by phone ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Provider phone: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, answer);
        searchedProvider.setPhone(answer);
    }
    else{
        searchedProvider.setPhone("");
    }

    std::cout << "Search by address ? (Y/N): ";
    do{
        std::cin >> answer;
        answer = str_tolower(answer);
    }
    while(answer != "y" && answer != "n");
    if(answer == "y"){
        std::cout << "  Provider address: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, answer);
        searchedProvider.setAddress(answer);
    }
    else{
        searchedProvider.setAddress("");
    }

    std::list<Provider> result;
    std::list<Provider>::iterator iter = this->providers.begin();
    std::list<Provider>::iterator last = this->providers.end();

    while((iter = std::find_if(iter, last,
        [&](Provider provider){
            return (searchedProvider.getId() == -1 || searchedProvider.getId() == provider.getId())
                    && (searchedProvider.getName() == "" || str_tolower(searchedProvider.getName()) == str_tolower(provider.getName()))
                    && (searchedProvider.getPhone() == "" || str_tolower(searchedProvider.getPhone()) == str_tolower(provider.getPhone()))
                    && (searchedProvider.getAddress() == "" || str_tolower(searchedProvider.getAddress()) == str_tolower(provider.getAddress()));
        })) != last)
    {
        result.push_back(*iter);
        iter++;
    }

    std::cout << "======== Search Results ========" << std::endl << std::endl;
    for(std::list<Provider>::iterator iter = result.begin(); iter != result.end(); iter++){
        iter->display();
        std::cout << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

void Providers::edit(){
    long id;
    Provider provider;
    std::list<Provider>::iterator iter;

    this->display();

    std::cout << "Provider ID: ";
    std::cin >> id;

    iter = std::find_if(this->providers.begin(), this->providers.end(),
        [&](Provider currentProvider){
            return currentProvider.getId() == id;
        }
    );

    if(iter == this->providers.end()){
        std::cout << "Provider does not exist!" << std::endl;
    }
    else{
        provider.setId(id);
        provider.scan();
        *iter = provider;
        std::cout << "Provider successfully modified!" << std::endl;
    }
}

void Providers::remove(ProviderOrders& providerOrdersList){
    long id;
    std::list<Provider>::iterator iter;

    this->display();
    std::cout << "Provider ID: ";
    std::cin >> id;

    iter = std::find_if(this->providers.begin(), this->providers.end(),
        [&](Provider currentProvider){
            return currentProvider.getId() == id;
        }
    );

    if(iter == this->providers.end()){
        std::cout << "Provider does not exist!" << std::endl;
    }
    else{
        providerOrdersList.removeByProvider(iter->getId());

        this->providers.erase(iter);

        std::cout << "Provider successfully deleted!" << std::endl;
    }

}

long Providers::generateId(){
    long id = 0;
    for(std::list<Provider>::iterator iter = this->providers.begin(); iter != this->providers.end(); iter++){
        if(iter->getId() > id){
            id = iter->getId();
        }
    }

    return id + 1;
}

Provider* Providers::findById(long id){
    std::list<Provider>::iterator iter;
    iter = std::find_if(this->providers.begin(), this->providers.end(),
        [&](Provider provider) {
            return provider.getId() == id;
        }
    );
    if(iter != this->providers.end()){
        return &(*iter);
    }
    return nullptr;
}

void Providers::readFromFile(){
    std::ifstream file;
    file.open("providers.bin", std::ifstream::in | std::ifstream::binary);

    if(file.is_open()){
        boost::archive::text_iarchive inputArchive(file);
        inputArchive >> this->providers;
    }
}

void Providers::writeToFile(){
    std::ofstream file;
    file.open("providers.bin", std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    if(file.is_open()){
        boost::archive::text_oarchive outputArchive(file);
        outputArchive << this->providers;
    }
}



#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "medicines.h"
#include "providers.h"
#include "providerOrders.h"
#include "Purchases.h"

using namespace std;

void mainMenu(Medicines&, Providers&, ProviderOrders&, Purchases&);
void stockManagementMenu(Medicines&, Providers&, ProviderOrders&, Purchases&);
void providerManagementMenu(Medicines&, Providers&, ProviderOrders&, Purchases&);
void orderManagementMenu(Medicines&, Providers&, ProviderOrders&, Purchases&);
void purchaseManagementMenu(Medicines&, Providers&, ProviderOrders&, Purchases&);

void purchaseManagementMenu(Medicines& medicinesList, Providers& providersList, ProviderOrders& providerOrdersList, Purchases& purchasesList){
    char answer;

    while(1){
        system("cls");

        std::cout << "-------------------------------------------------------------" << std::endl;
        std::cout << "==================== Purchase Management ====================" << std::endl;
        std::cout << "-------------------------------------------------------------" << std::endl;
        std::cout << "                   Please choose an option                   " << std::endl;
        std::cout << "                                                             " << std::endl;
        std::cout << "                    1 - Display Purchases                    " << std::endl;
        std::cout << "                    2 - Add Purchase                         " << std::endl;
        std::cout << "                    3 - Search Purchase                      " << std::endl;
        std::cout << "                    4 - Edit Purchase                        " << std::endl;
        std::cout << "                    5 - Remove Purchase                      " << std::endl;
        std::cout << "                    6 - Main Menu                            " << std::endl;
        std::cout << "-------------------------------------------------------------" << std::endl;

        do{
            std::cin >> answer;
        }
        while(answer != '1' && answer != '2' && answer != '3' && answer != '4' && answer != '5' && answer != '6');

         if(answer == '6'){
            break;
        }

        system("cls");

        switch(answer){
        case '1':
            purchasesList.display();
            break;
        case '2':
            purchasesList.add(medicinesList);
            break;
        case '3':
            purchasesList.search();
            break;
        case '4':
            purchasesList.edit(medicinesList);
            break;
        case '5':
            purchasesList.remove(medicinesList);
            break;
        }

        system("pause");
    }
}

void orderManagementMenu(Medicines& medicinesList, Providers& providersList, ProviderOrders& providerOrdersList, Purchases& purchasesList){
    char answer;

    while(1){
        system("cls");

        std::cout << "--------------------------------------------------------------" << std::endl;
        std::cout << "====================== Order Management ======================" << std::endl;
        std::cout << "--------------------------------------------------------------" << std::endl;
        std::cout << "                    Please choose an option                   " << std::endl;
        std::cout << "                                                              " << std::endl;
        std::cout << "                     1 - Display Orders                       " << std::endl;
        std::cout << "                     2 - Deliver Order                        " << std::endl;
        std::cout << "                     3 - Add Order                            " << std::endl;
        std::cout << "                     4 - Search Order                         " << std::endl;
        std::cout << "                     5 - Edit Order                           " << std::endl;
        std::cout << "                     6 - Remove Order                         " << std::endl;
        std::cout << "                     7 - Main Menu                            " << std::endl;
        std::cout << "--------------------------------------------------------------" << std::endl;

        do{
            std::cin >> answer;
        }
        while(answer != '1' && answer != '2' && answer != '3' && answer != '4' && answer != '5' && answer != '6' && answer != '7');

        if(answer == '7'){
            break;
        }

        system("cls");

        switch(answer){
        case '1':
            providerOrdersList.display();
            break;
        case '2':
            providerOrdersList.deliver(medicinesList);
            break;
        case '3':
            providerOrdersList.add(providersList);
            break;
        case '4':
            providerOrdersList.search(providersList);
            break;
        case '5':
            providerOrdersList.edit(providersList);
            break;
        case '6':
            providerOrdersList.remove();
            break;
        }

        system("pause");
    }
}

void providerManagementMenu(Medicines& medicinesList, Providers& providersList, ProviderOrders& providerOrdersList, Purchases& purchasesList){
    char answer;

    while(1){
        system("cls");

        std::cout << "-------------------------------------------------------------" << std::endl;
        std::cout << "==================== Provider Management ====================" << std::endl;
        std::cout << "-------------------------------------------------------------" << std::endl;
        std::cout << "                   Please choose an option                   " << std::endl;
        std::cout << "                                                             " << std::endl;
        std::cout << "                    1 - Display Providers                    " << std::endl;
        std::cout << "                    2 - Add Provider                         " << std::endl;
        std::cout << "                    3 - Search Provider                      " << std::endl;
        std::cout << "                    4 - Edit Provider                        " << std::endl;
        std::cout << "                    5 - Remove Provider                      " << std::endl;
        std::cout << "                    6 - Main Menu                            " << std::endl;
        std::cout << "-------------------------------------------------------------" << std::endl;

        do{
            std::cin >> answer;
        }
        while(answer != '1' && answer != '2' && answer != '3' && answer != '4' && answer != '5' && answer != '6');

        if(answer == '6'){
            break;
        }

        system("cls");

        switch(answer){
        case '1':
            providersList.display();
            break;
        case '2':
            providersList.add();
            break;
        case '3':
            providersList.search();
            break;
        case '4':
            providersList.edit();
            break;
        case '5':
            providersList.remove(providerOrdersList);
            break;
        }

        system("pause");
    }
}

void stockManagementMenu(Medicines& medicinesList, Providers& providersList, ProviderOrders& providerOrdersList, Purchases& purchasesList){
    char answer;

    while(1){
        system("cls");

        std::cout << "----------------------------------------------------------" << std::endl;
        std::cout << "==================== Stock Management ====================" << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;
        std::cout << "                  Please choose an option                 " << std::endl;
        std::cout << "                                                          " << std::endl;
        std::cout << "                   1 - Display Medicines                  " << std::endl;
        std::cout << "                   2 - Add Medicine                       " << std::endl;
        std::cout << "                   3 - Search Medicine                    " << std::endl;
        std::cout << "                   4 - Edit Medicine                      " << std::endl;
        std::cout << "                   5 - Remove Medicine                    " << std::endl;
        std::cout << "                   6 - Main Menu                          " << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;

        do{
            std::cin >> answer;
        }
        while(answer != '1' && answer != '2' && answer != '3' && answer != '4' && answer != '5' && answer != '6');

        if(answer == '6'){
            break;
        }

        system("cls");

        switch(answer){
        case '1':
            medicinesList.display();
            break;
        case '2':
            medicinesList.add();
            break;
        case '3':
            medicinesList.search();
            break;
        case '4':
            medicinesList.edit();
            break;
        case '5':
            medicinesList.remove();
            break;
        }

        system("pause");
    }
}

void mainMenu(Medicines& medicinesList, Providers& providersList, ProviderOrders& providerOrdersList, Purchases& purchasesList){
    char answer;

    while(1){
        system("cls");

        std::cout << "----------------------------------------------------------" << std::endl;
        std::cout << "==================== Pharmacy Manager ====================" << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;
        std::cout << "               Welcome! Please choose an option           " << std::endl;
        std::cout << "                                                          " << std::endl;
        std::cout << "                  1 - Stock Management                    " << std::endl;
        std::cout << "                  2 - Provider Management                 " << std::endl;
        std::cout << "                  3 - Order Management                    " << std::endl;
        std::cout << "                  4 - Purchase Management                 " << std::endl;
        std::cout << "                  5 - Save & Exit                         " << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;

        do{
            std::cin >> answer;
        }
        while(answer != '1' && answer != '2' && answer != '3' && answer != '4' && answer != '5');

        if(answer == '5'){
            break;
        }

        switch(answer){
        case '1':
            stockManagementMenu(medicinesList, providersList, providerOrdersList, purchasesList);
            break;
        case '2':
            providerManagementMenu(medicinesList, providersList, providerOrdersList, purchasesList);
            break;
        case '3':
            orderManagementMenu(medicinesList, providersList, providerOrdersList, purchasesList);
            break;
        case '4':
            purchaseManagementMenu(medicinesList, providersList, providerOrdersList, purchasesList);
            break;
        }
    }
}

int main()
{
    Medicines medicinesList;
    Providers providersList;
    ProviderOrders providerOrdersList;
    Purchases purchasesList;

    medicinesList.readFromFile();
    providersList.readFromFile();
    providerOrdersList.readFromFile();
    purchasesList.readFromFile();

    mainMenu(medicinesList, providersList, providerOrdersList, purchasesList);

    medicinesList.writeToFile();
    providersList.writeToFile();
    providerOrdersList.writeToFile();
    purchasesList.writeToFile();

    return 0;
}

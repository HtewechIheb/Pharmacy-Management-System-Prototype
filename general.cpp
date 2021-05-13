#include <iostream>
#include "general.h"

std::string str_tolower(std::string str){
    std::string str_lower;

    str_lower = str;
    for(unsigned int i = 0; i < str_lower.length(); i++){
        str_lower[i] = std::tolower(str_lower[i]);
    }
    return str_lower;
}

std::time_t dateScan(){
    std::tm date = {};

    std::cout << "  Day: ";
    std::cin >> date.tm_mday;
    std::cout << "  Month: ";
    std::cin >> date.tm_mon;
    date.tm_mon--;
    std::cout << "  Year: ";
    std::cin >> date.tm_year;
    date.tm_year -= 1900;

    return std::mktime(&date);
}

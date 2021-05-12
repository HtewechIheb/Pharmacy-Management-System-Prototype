#include "general.h"

std::string str_tolower(std::string str){
    std::string str_lower;

    str_lower = str;
    for(unsigned int i = 0; i < str_lower.length(); i++){
        str_lower[i] = std::tolower(str_lower[i]);
    }
    return str_lower;
}

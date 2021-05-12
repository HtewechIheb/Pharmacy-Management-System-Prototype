#include <iostream>
#include "medicine.h"

MedicineEnumMaps::MedicineEnumMaps(){
    typeMap.insert(std::pair<Type, std::string>(Type::LIQUID, "Liquid"));
    typeMap.insert(std::pair<Type, std::string>(Type::TABLET, "Tablet"));
    typeMap.insert(std::pair<Type, std::string>(Type::CAPSULES, "Capsules"));
    typeMap.insert(std::pair<Type, std::string>(Type::TOPICAL, "Topical"));
    typeMap.insert(std::pair<Type, std::string>(Type::SUPPOSITORY, "Suppository"));
    typeMap.insert(std::pair<Type, std::string>(Type::DROP, "Drop"));
    typeMap.insert(std::pair<Type, std::string>(Type::INHALER, "Inhaler"));
    typeMap.insert(std::pair<Type, std::string>(Type::INJECTION, "Injection"));
    typeMap.insert(std::pair<Type, std::string>(Type::IMPLANT, "Implant"));

    categoryMap.insert(std::pair<Category, std::string>(Category::ANTI_INFLAMMATORY, "Anti-Inflammatory"));
    categoryMap.insert(std::pair<Category, std::string>(Category::ANTI_DEPRESSANT, "Anti-Depressant"));
    categoryMap.insert(std::pair<Category, std::string>(Category::ANTI_BIOTIC, "Anti-Biotic"));
    categoryMap.insert(std::pair<Category, std::string>(Category::ANESTHETIC, "Anesthetic"));
    categoryMap.insert(std::pair<Category, std::string>(Category::ANTIVIRAL, "Antiviral"));
    categoryMap.insert(std::pair<Category, std::string>(Category::DIURETIC, "Diuretic"));
    categoryMap.insert(std::pair<Category, std::string>(Category::LAXATIVE, "Laxative"));
    categoryMap.insert(std::pair<Category, std::string>(Category::SEDATIVE, "Sedative"));
}

std::map<Type, std::string> MedicineEnumMaps::getTypeMap(){
    return typeMap;
}

std::map<Category, std::string> MedicineEnumMaps::getCategoryMap(){
    return categoryMap;
}

Medicine::Medicine(std::string name, Type type, Category category, double price, std::time_t creationDate, std::time_t consumptionDelay){
    this->id = -1;
    this->name = name;
    this->type = type;
    this->category = category;
    this->price = price;
    this->creationDate = creationDate;
    this->consumptionDelay = consumptionDelay;
}

void Medicine::display(){
    MedicineEnumMaps medicineEnumMaps;

    std::cout << "Id: " << this->id << std::endl;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Type: " << medicineEnumMaps.getTypeMap()[this->type] << std::endl;
    std::cout << "Category: " << medicineEnumMaps.getCategoryMap()[this->category] << std::endl;
    std::cout << "Price: " << this->price << std::endl;
    std::cout << "Creation Date: " << this->getCreationDateAsString() << std::endl;
    std::cout << "Consumption Delay: " << this->getConsumptionDelayAsString() << std::endl;
}

template<class T>
T enumScan(std::map<T, std::string> Tmap){
    int enumChoice;

    for(int typeIter = 1; typeIter != static_cast<int>(T::LAST); typeIter++){
        std::cout << "  " << typeIter << ": " << Tmap[static_cast<T>(typeIter)] << std::endl;
    }
    do{
        std::cin >> enumChoice;
    }
    while(enumChoice < 1 || enumChoice >= static_cast<int>(T::LAST));
    return static_cast<T>(enumChoice);
}

std::time_t dateScan(){
    std::tm date = {};
    std::cout << "  Day: ";
    std::cin >> date.tm_mday;
    std::cout << "  Month: ";
    std::cin >> date.tm_mon;
    std::cout << "  Year: ";
    std::cin >> date.tm_year;
    date.tm_year -= 1900;

    return std::mktime(&date);
}

void Medicine::scan(){
    MedicineEnumMaps medicineEnumMaps;

    std::cout << "Medicine ID: " << std::endl;
    std::cin >> this->id;
    std::cout << "Medicine Name: " << std::endl;
    std::cin >> this->name;
    std::cout << "Medicine Type: " << std::endl;
    this->type = enumScan<Type>(medicineEnumMaps.getTypeMap());
    std::cout << "Medicine Category: " << std::endl;
    this->category = enumScan<Category>(medicineEnumMaps.getCategoryMap());
    std::cout << "Medicine Price: " << std::endl;
    std::cin >> this->price;
    std::cout << "Medicine Creation Date: " << std::endl;
    this->creationDate = dateScan();
    std::cout << "Medicine Consumption Delay: " << std::endl;
    this->consumptionDelay = dateScan();
}

long Medicine::getId(){
    return this->id;
}

std::string Medicine::getName(){
    return this->name;
}

Type Medicine::getType(){
    return this->type;
}

Category Medicine::getCategory(){
    return this->category;
}

double Medicine::getPrice(){
    return this->price;
}

time_t Medicine::getCreationDate(){
    return this->creationDate;
}

time_t Medicine::getConsumptionDelay(){
    return this->consumptionDelay;
}

struct tm* Medicine::getCreationDateAsStruct(){
    return std::gmtime(&this->creationDate);
};

struct tm* Medicine::getConsumptionDelayAsStruct(){
    return std::gmtime(&this->consumptionDelay);
};

std::string Medicine::getCreationDateAsString(){
    char dateString[100];
    std::strftime(dateString, sizeof(dateString), "%d/%m/%Y", gmtime(&this->creationDate));
    return dateString;
};

std::string Medicine::getConsumptionDelayAsString(){
    char dateString[100];
    std::strftime(dateString, sizeof(dateString), "%d/%m/%Y", gmtime(&this->consumptionDelay));
    return dateString;
};


void Medicine::setId(long id){
    this->id = id;
}

void Medicine::setName(std::string name){
    this->name = name;
}

void Medicine::setType(Type type){
    this->type = type;
}

void Medicine::setCategory(Category category){
    this->category = category;
}

void Medicine::setPrice(double price){
    this->price = price;
}

void Medicine::setCreationDate(std::time_t creationDate){
    this->creationDate = creationDate;
}

void Medicine::setConsumptionDelay(std::time_t consumptionDelay){
    this->consumptionDelay = consumptionDelay;
}


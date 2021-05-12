#include <string>
#include <map>
#include <ctime>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#ifndef MEDICINE_H
#define MEDICINE_H

enum class Type {
    LIQUID,
    TABLET,
    CAPSULES,
    TOPICAL,
    SUPPOSITORY,
    DROP,
    INHALER,
    INJECTION,
    IMPLANT,
    LAST,
    NONE
};

enum class Category {
    ANTI_INFLAMMATORY,
    ANTI_DEPRESSANT,
    ANTI_BIOTIC,
    ANESTHETIC,
    ANTIVIRAL,
    DIURETIC,
    LAXATIVE,
    SEDATIVE,
    LAST,
    NONE
};

class MedicineEnumMaps {
    std::map<Type, std::string> typeMap;
    std::map<Category, std::string> categoryMap;

public:
    MedicineEnumMaps();
    ~MedicineEnumMaps() { };
    std::map<Type, std::string> getTypeMap();
    std::map<Category, std::string> getCategoryMap();
};

template<class T>
T enumScan(std::map<T, std::string>);

std::time_t dateScan();

class Medicine {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & id;
        ar & name;
        ar & type;
        ar & category;
        ar & price;
        ar & creationDate;
        ar & consumptionDelay;
    }
    long id;
    std::string name;
    Type type;
    Category category;
    double price;
    std::time_t creationDate;
    std::time_t consumptionDelay;

public:
    Medicine() { }
    ~Medicine() { }
    Medicine(std::string, Type, Category, double, std::time_t, std::time_t);
    void display();
    void scan();
    void deliveryScan();

    long getId();
    std::string getName();
    Type getType();
    Category getCategory();
    double getPrice();
    std::time_t getCreationDate();
    std::time_t getConsumptionDelay();
    std::tm* getCreationDateAsStruct();
    std::tm* getConsumptionDelayAsStruct();
    std::string getCreationDateAsString();
    std::string getConsumptionDelayAsString();

    void setId(long);
    void setName(std::string);
    void setType(Type);
    void setCategory(Category);
    void setPrice(double);
    void setCreationDate(std::time_t);
    void setConsumptionDelay(std::time_t);
};

#endif // MEDICINE_H

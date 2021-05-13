#include <map>
#include "general.h"
#include "medicines.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>

#ifndef PURCHASE_H
#define PURCHASE_H

class Purchase {
    long id;
    std::list<Medicine> medicines;
    double total;
    std::time_t date;

public:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & id;
        ar & medicines;
        ar & total;
        ar & date;
    }

    Purchase() { };
    ~Purchase() { };
    Purchase(std::list<Medicine>, double, std::time_t);
    void display();
    void scan(Medicines&);
    void addMedicine(Medicine);
    void clearMedicines();

    long getId();
    std::list<Medicine> getMedicines();
    double getTotal();
    std::time_t getDate();
    std::tm* getDateAsStruct();
    std::string getDateAsString();

    void setId(long);
    void setMedicines(std::list<Medicine>);
    void setTotal(double);
    void setDate(std::time_t);
};

#endif // PURCHASE_H

#include <list>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include "medicine.h"

#ifndef MEDICINES_H
#define MEDICINES_H

class Medicines {
    std::list<Medicine> medicines;

public:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & medicines;
    }
    Medicines() { };
    ~Medicines() { };
    Medicines(std::list<Medicine>);
    void display();
    void add();
    void search();
    void edit();
    void remove();
    long generateId();
    void readFromFile();
    void writeToFile();

    void add(Medicine);
    void remove(long);
    Medicine* findById(long);
    Medicine* findByName(std::string);
};

#endif // MEDICINES_H

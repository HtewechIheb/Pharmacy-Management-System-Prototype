#ifndef MEDICINES_H
#define MEDICINES_H

#include <list>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include "medicine.h"

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

    // User interactive methods
    void display();
    void add();
    void search();
    void edit();
    void remove();
    //

    void readFromFile();
    void writeToFile();

    long generateId();
    void add(Medicine);
    void remove(long);
    Medicine* findById(long);
    Medicine* findByName(std::string);
};

#endif // MEDICINES_H

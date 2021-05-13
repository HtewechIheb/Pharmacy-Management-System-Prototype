#include <list>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include "purchase.h"

#ifndef PURCHASES_H
#define PURCHASES_H

class Purchases {
    std::list<Purchase> purchases;

public:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & purchases;
    }
    Purchases() { };
    ~Purchases() { };
    Purchases(std::list<Purchase>);
    void display();
    void add(Medicines&);
    void search();
    void edit(Medicines&);
    void remove(Medicines&);
    void readFromFile();
    void writeToFile();
};

#endif // PURCHASES_H


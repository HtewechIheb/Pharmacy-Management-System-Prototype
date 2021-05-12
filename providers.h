#include <list>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include "provider.h"

#ifndef PROVIDERS_H
#define PROVIDERS_H

class Providers {
    std::list<Provider> providers;

public:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & providers;
    }
    Providers() { };
    ~Providers() { };
    Providers(std::list<Provider>);
    void display();
    void add();
    void search();
    void edit();
    void remove();
    void readFromFile();
    void writeToFile();

    Provider* find(long);
};

#endif // PROVIDERS_H


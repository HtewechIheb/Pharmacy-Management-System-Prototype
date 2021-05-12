#include <list>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include "providerOrder.h"

#ifndef PROVIDER_ORDERS_H
#define PROVIDER_ORDERS_H

class ProviderOrders {
    std::list<ProviderOrder> providerOrders;

public:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & providerOrders;
    }
    ProviderOrders() { };
    ~ProviderOrders() { };
    ProviderOrders(std::list<ProviderOrder>);
    void display();
    void add(Providers, Medicines);
    void search(Providers);
    void edit(Providers, Medicines);
    void remove();
    void readFromFile();
    void writeToFile();
};

#endif // PROVIDER_ORDERS_H

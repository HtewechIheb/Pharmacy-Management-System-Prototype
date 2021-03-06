#ifndef PROVIDER_ORDERS_H
#define PROVIDER_ORDERS_H

#include <list>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include "providerOrder.h"
#include "providers.h"

class ProviderOrder;
class Medicines;
class Providers;

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

    // User interactive methods
    void deliver(Medicines&);
    void add(Providers);
    void search(Providers);
    void edit(Providers);
    void remove();
    //

    void readFromFile();
    void writeToFile();

    long generateId();
    void removeByProvider(long);
};

#endif // PROVIDER_ORDERS_H

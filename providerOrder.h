#ifndef PROVIDER_ORDER_H
#define PROVIDER_ORDER_H

#include <map>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include "providers.h"
#include "medicines.h"

class Providers;

class ProviderOrder {
    long id;
    Provider provider;
    std::map<std::string, int> medicines;
    bool delivered;

public:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & id;
        ar & provider;
        ar & medicines;
        ar & delivered;
    }

    ProviderOrder() { };
    ~ProviderOrder() { };
    ProviderOrder(Provider, std::map<std::string, int>, bool);
    void display();
    void scan(Providers);
    void deliver(Medicines& medicines);

    long getId();
    Provider getProvider();
    std::map<std::string, int> getMedicines();
    bool getDelivered();

    void setId(long);
    void setProvider(Provider);
    void setMedicines(std::map<std::string, int>);
    void setDelivered(bool);
};

#endif // PROVIDER_ORDER_H

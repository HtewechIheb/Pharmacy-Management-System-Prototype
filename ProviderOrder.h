#include <map>
#include "provider.h"
#include "providers.h"

class ProviderOrder {
    long id;
    Provider provider;
    std::map<string, int> medicines;
    bool delivered;

public:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & id;
        ar & providerId;
        ar & medicines;
        ar & delivered;
    }

    ProviderOrder() { };
    ~ProviderOrder() { };
    ProviderOrder(Provider, std::map<string, int>, bool);
    void display();
    void scan();

    long getId();
    Provider getProvider();
    std::map<string, int> getMedicines();
    std::string getDelivered();

    void setId(long);
    void setProvider(Provider);
    void setMedicines(std::map<string, int>);
    void setDelivered(std::string);
}

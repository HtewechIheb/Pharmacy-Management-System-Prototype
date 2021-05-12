#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#ifndef PROVIDER_H
#define PROVIDER_H

class Provider {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & id;
        ar & name;
        ar & phone;
        ar & address;
    }
    long id;
    std::string name;
    std::string phone;
    std::string address;

public:
    Provider() { }
    ~Provider() { }
    Provider(std::string, std::string, std::string);
    void display();
    void scan();

    long getId();
    std::string getName();
    std::string getPhone();
    std::string getAddress();

    void setId(long);
    void setName(std::string);
    void setPhone(std::string);
    void setAddress(std::string);
};

#endif // PROVIDER_H

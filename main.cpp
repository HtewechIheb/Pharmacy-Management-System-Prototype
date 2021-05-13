#include <iostream>
#include <ctime>
#include <algorithm>
#include "medicine.h"
#include "medicines.h"
#include "provider.h"
#include "providers.h"
#include "providerOrder.h"
#include "providerOrders.h"
#include "Purchase.h"
#include "Purchases.h"

using namespace std;

int main()
{
    /************************* TEST CODE *******************************/

    time_t creationDate = time(NULL);
    struct tm buffer = *gmtime(&creationDate);
    buffer.tm_mon += 3;
    time_t consumptionDate = mktime(&buffer);

    Medicine med1("Panadol", Type::CAPSULES, Category::SEDATIVE, 25.00, creationDate, consumptionDate);
    Medicine med2("Gripex", Type::CAPSULES, Category::SEDATIVE, 25.00, creationDate, consumptionDate);
    Medicine med3("Clamoxyl", Type::CAPSULES, Category::SEDATIVE, 25.00, creationDate, consumptionDate);
    Medicine med4("Minoxidil", Type::CAPSULES, Category::SEDATIVE, 25.00, creationDate, consumptionDate);
    Medicine med5("Minoxidil", Type::CAPSULES, Category::SEDATIVE, 25.00, creationDate, consumptionDate);

    Provider pro1("Provider X", "44658792", "RUE X");
    Provider pro2("Provider Y", "44658792", "RUE X");
    Provider pro3("Provider Z", "44658792", "RUE X");

    std::list<Provider> temp;
    pro1.setId(101);
    pro2.setId(102);
    pro3.setId(103);
    temp.push_back(pro1);
    temp.push_back(pro2);
    temp.push_back(pro3);

    /*std::list<Medicine> temp;
    med1.setId(101);
    med2.setId(102);
    med3.setId(103);
    med4.setId(104);
    med5.setId(105);
    temp.push_back(med1);
    temp.push_back(med2);
    temp.push_back(med3);
    temp.push_back(med4);
    temp.push_back(med5);*/
    //Providers pros(temp);
    //pros.display();




    Medicines meds;
    meds.readFromFile();
    meds.display();

    Purchases purs;
    purs.add(meds);
    purs.add(meds);
    meds.display();
    purs.display();
    purs.search();
    //proOrds.search(pros);
    //meds.display();
    //meds.add();
    /*meds.display();
    meds.edit();
    meds.display();
    meds.remove();
    meds.display();*/
    //meds.search();
    //temp = meds.search(-1, "Minoxidil", Type::CAPSULES, Category::SEDATIVE);
    //std::for_each(temp.begin(), temp.end(), [](Medicine medicine) {medicine.display();});


    return 0;
}

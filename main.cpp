#include <iostream>
#include <ctime>
#include <algorithm>
#include "medicine.h"
#include "medicines.h"

using namespace std;

int main()
{
    time_t creationDate = time(NULL);
    struct tm buffer = *gmtime(&creationDate);
    buffer.tm_mon += 3;
    time_t consumptionDate = mktime(&buffer);

    Medicine med1("Panadol", Type::CAPSULES, Category::SEDATIVE, 25.00, creationDate, consumptionDate);
    Medicine med2("Gripex", Type::CAPSULES, Category::SEDATIVE, 25.00, creationDate, consumptionDate);
    Medicine med3("Clamoxyl", Type::CAPSULES, Category::SEDATIVE, 25.00, creationDate, consumptionDate);
    Medicine med4("Minoxidil", Type::CAPSULES, Category::SEDATIVE, 25.00, creationDate, consumptionDate);
    Medicine med5("Minoxidil", Type::CAPSULES, Category::SEDATIVE, 25.00, creationDate, consumptionDate);
    std::list<Medicine> temp;
    med1.setId(101);
    med2.setId(102);
    med3.setId(103);
    med4.setId(104);
    med5.setId(105);
    temp.push_back(med1);
    temp.push_back(med2);
    temp.push_back(med3);
    temp.push_back(med4);
    temp.push_back(med5);


    Medicines meds;
    meds.readFromFile();
    meds.display();
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

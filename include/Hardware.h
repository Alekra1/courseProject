#ifndef HARDWARE_H
#define HARDWARE_H

#include "ComputerPart.h"

using namespace std;

class Hardware : public ComputerPart {
protected:
    string manufacturer;
    int warrantyPeriod;

public:
    Hardware(string id, string n, double p, int q,
             string mfr, int warranty)
        : ComputerPart(id, n, p, q), manufacturer(mfr), warrantyPeriod(warranty) {}

    string getManufacturer() const { return manufacturer; }
    int getWarrantyPeriod() const { return warrantyPeriod; }
};

#endif 
#ifndef HARDWARE_H
#define HARDWARE_H

#include "ComputerPart.h"

using std::string;

class Hardware : public ComputerPart {
protected:
    string manufacturer;
    int warrantyPeriod;

public:
    Hardware(const string& id, const string& n, double p, int q,
             const string& mfr, int warranty)
        : ComputerPart(id, n, p, q), manufacturer(mfr), warrantyPeriod(warranty) {}

    string getManufacturer() const { return manufacturer; }
    int getWarrantyPeriod() const { return warrantyPeriod; }
};

#endif 
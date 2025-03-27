#ifndef HARDWARE_H
#define HARDWARE_H

#include "ComputerPart.h"

class Hardware : public ComputerPart {
protected:
    std::string manufacturer;
    int warrantyPeriod;

public:
    // Constructor
    Hardware(const std::string& id, const std::string& n, double p, int q,
             const std::string& mfr, int warranty)
        : ComputerPart(id, n, p, q), manufacturer(mfr), warrantyPeriod(warranty) {}

    // Getters
    std::string getManufacturer() const { return manufacturer; }
    int getWarrantyPeriod() const { return warrantyPeriod; }
};

#endif // HARDWARE_H 
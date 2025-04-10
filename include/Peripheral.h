#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include "ComputerPart.h"

using std::string;

class Peripheral : public ComputerPart {
protected:
    string brand;
    string connectivityType;

public:
    Peripheral(const string& id, const string& n, double p, int q,
               const string& b, const string& conn)
        : ComputerPart(id, n, p, q), brand(b), connectivityType(conn) {}

    string getBrand() const { return brand; }
    string getConnectivityType() const { return connectivityType; }
};

#endif 
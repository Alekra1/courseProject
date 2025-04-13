#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include "ComputerPart.h"

using namespace std;

class Peripheral : public ComputerPart {
protected:
    string brand;
    string connectivityType;

public:
    Peripheral(string id, string n, double p, int q,
               string b, string conn)
        : ComputerPart(id, n, p, q), brand(b), connectivityType(conn) {}

    string getBrand() const { return brand; }
    string getConnectivityType() const { return connectivityType; }
};

#endif 
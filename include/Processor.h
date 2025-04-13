#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "Hardware.h"
#include <map>

using namespace std;

class Processor : public Hardware {
private:
    double clockSpeed;
    int coreCount;
    string socketType;

public:
    Processor(string id, string n, double p, int q,
              string mfr, int warranty,
              double clock, int cores, string socket)
        : Hardware(id, n, p, q, mfr, warranty),
          clockSpeed(clock), coreCount(cores), socketType(socket) {}

    void displayDetails(bool detailed = false) const override;
    pair<double, double> computeAdditionalMetrics() const override;
    double getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const override;
    string getTypeString() const override;
    void writeDataToStream(ofstream& out) const override;

    double getClockSpeed() const { return clockSpeed; }
    int getCoreCount() const { return coreCount; }
    string getSocketType() const { return socketType; }
};

#endif
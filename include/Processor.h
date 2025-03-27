#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "Hardware.h"

using std::string;

class Processor : public Hardware {
private:
    double clockSpeed;
    int coreCount;
    string socketType;

public:
    // Constructor
    Processor(const string& id, const string& n, double p, int q,
              const string& mfr, int warranty,
              double clock, int cores, const string& socket)
        : Hardware(id, n, p, q, mfr, warranty),
          clockSpeed(clock), coreCount(cores), socketType(socket) {}

    // Implementation of virtual methods
    void displayDetails(bool detailed = false) override;
    std::pair<double, double> computeAdditionalMetrics() override;
    double getCompatibilityRate(const string& userPreference, const string& budgetCategory) override;

    // Getters
    double getClockSpeed() const { return clockSpeed; }
    int getCoreCount() const { return coreCount; }
    string getSocketType() const { return socketType; }
};

#endif // PROCESSOR_H 
#ifndef GRAPHICS_CARD_H
#define GRAPHICS_CARD_H

#include "Hardware.h"

using std::string;

class GraphicsCard : public Hardware {
private:
    int memorySize;      // in GB
    double coreClock;    // in MHz
    double memoryClock;  // in MHz

public:
    // Constructor
    GraphicsCard(const string& id, const string& n, double p, int q,
                 const string& mfr, int warranty,
                 int memSize, double core, double mem)
        : Hardware(id, n, p, q, mfr, warranty),
          memorySize(memSize), coreClock(core), memoryClock(mem) {}

    // Implementation of virtual methods
    void displayDetails(bool detailed = false) override;
    pair<double, double> computeAdditionalMetrics() override;
    double getCompatibilityRate(const string& userPreference, const string& budgetCategory) override;

    // Getters
    int getMemorySize() const { return memorySize; }
    double getCoreClock() const { return coreClock; }
    double getMemoryClock() const { return memoryClock; }
};

#endif // GRAPHICS_CARD_H 
#ifndef GRAPHICS_CARD_H
#define GRAPHICS_CARD_H

#include "Hardware.h"

using std::string;

class GraphicsCard : public Hardware {
private:
    int memorySize;
    double coreClock;
    double memoryClock;

public:
    GraphicsCard(const string& id, const string& n, double p, int q,
                 const string& mfr, int warranty,
                 int memSize, double core, double mem)
        : Hardware(id, n, p, q, mfr, warranty),
          memorySize(memSize), coreClock(core), memoryClock(mem) {}

    void displayDetails(bool detailed = false) const override;
    pair<double, double> computeAdditionalMetrics() const override;
    double getCompatibilityRate(const string& userPreference, const string& budgetCategory) const override;

    int getMemorySize() const { return memorySize; }
    double getCoreClock() const { return coreClock; }
    double getMemoryClock() const { return memoryClock; }
};

#endif
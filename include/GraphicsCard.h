#ifndef GRAPHICS_CARD_H
#define GRAPHICS_CARD_H

#include "Hardware.h"
#include <map>

using namespace std;

class GraphicsCard : public Hardware {
private:
    int memorySize;
    double coreClock;
    double memoryClock;

public:
    GraphicsCard(string id, string n, double p, int q,
                 string mfr, int warranty,
                 int memSize, double core, double mem)
        : Hardware(id, n, p, q, mfr, warranty),
          memorySize(memSize), coreClock(core), memoryClock(mem) {}

    void displayDetails(bool detailed = false) const override;
    pair<double, double> computeAdditionalMetrics() const override;
    double getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const override;
    string getTypeString() const override;
    void writeDataToStream(ofstream& out) const override;

    int getMemorySize() const { return memorySize; }
    double getCoreClock() const { return coreClock; }
    double getMemoryClock() const { return memoryClock; }
};

#endif
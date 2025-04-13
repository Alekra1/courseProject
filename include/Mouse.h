#ifndef MOUSE_H
#define MOUSE_H

#include "Peripheral.h"

using std::string;

class Mouse : public Peripheral {
private:
    int pollingRate;     
    double weight;      
    int numberOfButtons;

public:
    Mouse(const string& id, const string& n, double p, int q,
          const string& b, const string& conn,
          int pollRate, double w, int buttons)
        : Peripheral(id, n, p, q, b, conn),
          pollingRate(pollRate), weight(w), numberOfButtons(buttons) {}

    void displayDetails(bool detailed = false) const override;
    pair<double, double> computeAdditionalMetrics() const override;
    double getCompatibilityRate(const string& userPreference, const string& budgetCategory) const override;

    int getPollingRate() const { return pollingRate; }
    double getWeight() const { return weight; }
    int getNumberOfButtons() const { return numberOfButtons; }
};

#endif
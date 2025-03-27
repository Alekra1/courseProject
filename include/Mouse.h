#ifndef MOUSE_H
#define MOUSE_H

#include "Peripheral.h"

using std::string;

class Mouse : public Peripheral {
private:
    int pollingRate;     // in Hz
    double weight;       // in grams
    int numberOfButtons;

public:
    // Constructor
    Mouse(const string& id, const string& n, double p, int q,
          const string& b, const string& conn,
          int pollRate, double w, int buttons)
        : Peripheral(id, n, p, q, b, conn),
          pollingRate(pollRate), weight(w), numberOfButtons(buttons) {}

    // Implementation of virtual methods
    void displayDetails(bool detailed = false) override;
    pair<double, double> computeAdditionalMetrics() override;
    double getCompatibilityRate(const string& userPreference, const string& budgetCategory) override;

    // Getters
    int getPollingRate() const { return pollingRate; }
    double getWeight() const { return weight; }
    int getNumberOfButtons() const { return numberOfButtons; }
};

#endif // MOUSE_H 
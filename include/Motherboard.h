#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include "Hardware.h"

using std::string;

class Motherboard : public Hardware {
private:
    string chipset;
    string formFactor;
    string socket;

public:
    // Constructor
    Motherboard(const string& id, const string& n, double p, int q,
                const string& mfr, int warranty,
                const string& chip, const string& form, const string& sock)
        : Hardware(id, n, p, q, mfr, warranty),
          chipset(chip), formFactor(form), socket(sock) {}

    // Implementation of virtual methods
    void displayDetails(bool detailed = false) override;
    pair<double, double> computeAdditionalMetrics() override;
    double getCompatibilityRate(const string& userPreference, const string& budgetCategory) override;

    // Getters
    string getChipset() const { return chipset; }
    string getFormFactor() const { return formFactor; }
    string getSocket() const { return socket; }
};

#endif // MOTHERBOARD_H 
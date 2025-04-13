#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H

#include "Hardware.h"
#include <map>

using namespace std;

class Motherboard : public Hardware {
private:
    string chipset;
    string formFactor;
    string socket;

public:
    Motherboard(string id, string n, double p, int q,
                string mfr, int warranty,
                string chip, string form, string sock)
        : Hardware(id, n, p, q, mfr, warranty),
          chipset(chip), formFactor(form), socket(sock) {}

    void displayDetails(bool detailed = false) const override;
    pair<double, double> computeAdditionalMetrics() const override;
    double getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const override;
    string getTypeString() const override;
    void writeDataToStream(ofstream& out) const override;

    string getChipset() const { return chipset; }
    string getFormFactor() const { return formFactor; }
    string getSocket() const { return socket; }
};

#endif
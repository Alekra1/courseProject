#ifndef MOUSE_H
#define MOUSE_H

#include "Peripheral.h"
#include <map>

using namespace std;

class Mouse : public Peripheral {
private:
    int pollingRate;     
    double weight;      
    int numberOfButtons;

public:
    Mouse(string id, string n, double p, int q,
          string b, string conn,
          int pollRate, double w, int buttons)
        : Peripheral(id, n, p, q, b, conn),
          pollingRate(pollRate), weight(w), numberOfButtons(buttons) {}

    void displayDetails(bool detailed = false) const override;
    pair<double, double> computeAdditionalMetrics() const override;
    double getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const override;
    string getTypeString() const override;
    void writeDataToStream(ofstream& out) const override;

    int getPollingRate() const { return pollingRate; }
    double getWeight() const { return weight; }
    int getNumberOfButtons() const { return numberOfButtons; }
};

#endif
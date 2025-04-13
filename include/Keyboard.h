#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Peripheral.h"
#include <map>

using namespace std;

class Keyboard : public Peripheral {
private:
    string switchType;
    bool backlit;
    bool isHotSwappable;

public:
    Keyboard(string id, string n, double p, int q,
             string b, string conn,
             string switchT, bool back, bool hotSwap)
        : Peripheral(id, n, p, q, b, conn),
          switchType(switchT), backlit(back), isHotSwappable(hotSwap) {}

    void displayDetails(bool detailed = false) const override;
    pair<double, double> computeAdditionalMetrics() const override;
    double getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const override;
    string getTypeString() const override;
    void writeDataToStream(ofstream& out) const override;

    string getSwitchType() const { return switchType; }
    bool isBacklit() const { return backlit; }
    bool getIsHotSwappable() const { return isHotSwappable; }
};

#endif
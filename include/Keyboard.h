#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Peripheral.h"

using std::string;

class Keyboard : public Peripheral {
private:
    string switchType;
    bool backlit;
    bool isHotSwappable;

public:
    Keyboard(const string& id, const string& n, double p, int q,
             const string& b, const string& conn,
             const string& switchT, bool back, bool hotSwap)
        : Peripheral(id, n, p, q, b, conn),
          switchType(switchT), backlit(back), isHotSwappable(hotSwap) {}

    void displayDetails(bool detailed = false) override;
    pair<double, double> computeAdditionalMetrics() override;
    double getCompatibilityRate(const string& userPreference, const string& budgetCategory) override;

    string getSwitchType() const { return switchType; }
    bool isBacklit() const { return backlit; }
    bool isHotSwappable() const { return isHotSwappable; }
};

#endif
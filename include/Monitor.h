#ifndef MONITOR_H
#define MONITOR_H

#include "Peripheral.h"

using std::string;

class Monitor : public Peripheral {
private:
    double screenSize;    // in inches
    string resolution;    // e.g., "1920x1080"
    int refreshRate;      // in Hz
    string panelType;     // e.g., "IPS", "TN", "VA"

public:
    // Constructor
    Monitor(const string& id, const string& n, double p, int q,
            const string& b, const string& conn,
            double size, const string& res, int refresh, const string& panel)
        : Peripheral(id, n, p, q, b, conn),
          screenSize(size), resolution(res), refreshRate(refresh), panelType(panel) {}

    // Implementation of virtual methods
    void displayDetails(bool detailed = false) override;
    pair<double, double> computeAdditionalMetrics() override;
    double getCompatibilityRate(const string& userPreference, const string& budgetCategory) override;

    // Getters
    double getScreenSize() const { return screenSize; }
    string getResolution() const { return resolution; }
    int getRefreshRate() const { return refreshRate; }
    string getPanelType() const { return panelType; }
};

#endif // MONITOR_H 
#ifndef MONITOR_H
#define MONITOR_H

#include "Peripheral.h"

using std::string;

class Monitor : public Peripheral {
private:
    double screenSize;    
    string resolution;    
    int refreshRate;      
    string panelType;    

public:
    Monitor(const string& id, const string& n, double p, int q,
            const string& b, const string& conn,
            double size, const string& res, int refresh, const string& panel)
        : Peripheral(id, n, p, q, b, conn),
          screenSize(size), resolution(res), refreshRate(refresh), panelType(panel) {}

    void displayDetails(bool detailed = false) const override;
    pair<double, double> computeAdditionalMetrics() const override;
    double getCompatibilityRate(const string& userPreference, const string& budgetCategory) const override;

    double getScreenSize() const { return screenSize; }
    string getResolution() const { return resolution; }
    int getRefreshRate() const { return refreshRate; }
    string getPanelType() const { return panelType; }
};

#endif 
#ifndef MONITOR_H
#define MONITOR_H

#include "Peripheral.h"
#include <map>

using namespace std;

class Monitor : public Peripheral {
private:
    double screenSize;    
    string resolution;    
    int refreshRate;      
    string panelType;    

public:
    Monitor(string id, string n, double p, int q,
            string b, string conn,
            double size, string res, int refresh, string panel)
        : Peripheral(id, n, p, q, b, conn),
          screenSize(size), resolution(res), refreshRate(refresh), panelType(panel) {}

    void displayDetails(bool detailed = false) const override;
    pair<double, double> computeAdditionalMetrics() const override;
    double getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const override;
    string getTypeString() const override;
    void writeDataToStream(ofstream& out) const override;

    double getScreenSize() const { return screenSize; }
    string getResolution() const { return resolution; }
    int getRefreshRate() const { return refreshRate; }
    string getPanelType() const { return panelType; }
};

#endif 
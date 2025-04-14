#include "GraphicsCard.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>

using namespace std;

void GraphicsCard::displayDetails(bool detailed) const {
    cout << "----------------------------------------" << endl;
    cout << "Type: Graphics Card" << endl;
    cout << "ID: " << partID << endl;
    cout << "Name: " << name << endl;
    cout << fixed << setprecision(2);
    cout << "Price: $" << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Manufacturer: " << manufacturer << endl;
    cout << "Warranty: " << warrantyPeriod << " months" << endl;
    cout << "Memory Size: " << memorySize << " GB" << endl;
    cout << fixed << setprecision(2);
    cout << "Core Clock: " << coreClock << " MHz" << endl;
    cout << "Memory Clock: " << memoryClock << " MHz" << endl;

    if (detailed) {
        pair<double, double> metrics = computeAdditionalMetrics();
        cout << fixed << setprecision(2);
        cout << "Performance Score: " << metrics.first << endl;
        cout << "Price/Performance Ratio: " << metrics.second << endl;
    }
    cout << "----------------------------------------" << endl;
}

pair<double, double> GraphicsCard::computeAdditionalMetrics() const {
    double performance = (memorySize * 50.0) + (coreClock * 0.1) + (memoryClock * 0.05);
    double pricePerformanceRatio = (price > 0) ? performance / price : 0;
    return {performance, pricePerformanceRatio};
}

double GraphicsCard::getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const {
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double performance = metrics.first;

    if (budgetCategory == "low" && price > 300) return 1.0;
    if (budgetCategory == "medium" && (price < 150 || price > 800)) return 1.0;
    if (budgetCategory == "high" && price < 400) return 1.0;

    compatibilityScore += performance * 0.05;

    if (budgetCategory == "low" && price < 200) compatibilityScore += 30;
    else if (budgetCategory == "medium" && price >= 150 && price < 600) compatibilityScore += 30;
    else if (budgetCategory == "high" && price >= 500) compatibilityScore += 30;
    else compatibilityScore += 5;

    string userPreference = "";
    if (preferences.count("GPU")) {
        userPreference = preferences.at("GPU");
    }

    if (!userPreference.empty() && manufacturer.find(userPreference) != string::npos) {
        compatibilityScore += 20;
    } else {
        compatibilityScore += 5;
    }

    double maxPossibleScore = ((16 * 50.0) + (2000 * 0.1) + (18000 * 0.05)) * 0.05 + 40 + 20;
     if(maxPossibleScore <= 0) return 0;

    compatibilityScore = (compatibilityScore / maxPossibleScore) * 100.0;

    return min(max(compatibilityScore, 0.0), 100.0);
}

string GraphicsCard::getTypeString() const {
    return "GraphicsCard";
}

void GraphicsCard::writeDataToStream(ofstream& out) const {
    out << getTypeString() << ","
        << partID << ","
        << name << ","
        << price << ","
        << quantity << ","
        << manufacturer << ","
        << warrantyPeriod << ","
        << memorySize << ","
        << coreClock << ","
        << memoryClock << endl;
} 
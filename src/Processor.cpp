#include "Processor.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>

using namespace std;

void Processor::displayDetails(bool detailed) const {
    cout << "----------------------------------------" << endl;
    cout << "Type: Processor" << endl;
    cout << "ID: " << partID << endl;
    cout << "Name: " << name << endl;
    cout << fixed << setprecision(2);
    cout << "Price: $" << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Manufacturer: " << manufacturer << endl;
    cout << "Warranty: " << warrantyPeriod << " months" << endl;
    cout << "Socket: " << socketType << endl;
    cout << "Core Count: " << coreCount << endl;
    cout << "Clock Speed: " << clockSpeed << " GHz" << endl;

    if (detailed) {
        pair<double, double> metrics = computeAdditionalMetrics();
        cout << fixed << setprecision(2);
        cout << "Performance Score: " << metrics.first << endl;
        cout << "Price/Performance Ratio: " << metrics.second << endl;
    }
     cout << "----------------------------------------" << endl;
}

pair<double, double> Processor::computeAdditionalMetrics() const {
    double performance = coreCount * clockSpeed;
    double pricePerformanceRatio = (price > 0) ? performance / price : 0;
    return {performance, pricePerformanceRatio};
}

double Processor::getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const {
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double performance = metrics.first;

    if (budgetCategory == "low" && price > 200) return 1.0;
    if (budgetCategory == "medium" && (price < 100 || price > 500)) return 1.0;
    if (budgetCategory == "high" && price < 300) return 1.0;

    compatibilityScore += performance * 0.5;

    if (budgetCategory == "low" && price < 150) compatibilityScore += 30;
    else if (budgetCategory == "medium" && price >= 100 && price < 400) compatibilityScore += 30;
    else if (budgetCategory == "high" && price >= 300) compatibilityScore += 30;
    else compatibilityScore += 5;

    string userPreference = "";
    if (preferences.count("CPU")) { 
        userPreference = preferences.at("CPU");
    }

    if (!userPreference.empty() && manufacturer.find(userPreference) != string::npos) {
        compatibilityScore += 20;
    } else {
        compatibilityScore += 5;
    }

    double maxPossibleScore = (16 * 5.0 * 0.5) + 30 + 20;
    if(maxPossibleScore <= 0) return 0;

    compatibilityScore = (compatibilityScore / maxPossibleScore) * 100.0;

    return min(max(compatibilityScore, 0.0), 100.0);
}

string Processor::getTypeString() const {
    return "Processor";
}

void Processor::writeDataToStream(ofstream& out) const {
    out << getTypeString() << ","
        << partID << ","
        << name << ","
        << price << ","
        << quantity << ","
        << manufacturer << ","
        << warrantyPeriod << ","
        << clockSpeed << ","
        << coreCount << ","
        << socketType << endl;
} 
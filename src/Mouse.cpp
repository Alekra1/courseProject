#include "Mouse.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>

using namespace std;

void Mouse::displayDetails(bool detailed) const {
    cout << "----------------------------------------" << endl;
    cout << "Type: Mouse" << endl;
    cout << "ID: " << partID << endl;
    cout << "Name: " << name << endl;
    cout << fixed << setprecision(2);
    cout << "Price: $" << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Brand: " << brand << endl;
    cout << "Connectivity: " << connectivityType << endl;
    cout << "Polling Rate: " << pollingRate << " Hz" << endl;
    cout << fixed << setprecision(1);
    cout << "Weight: " << weight << " g" << endl;
    cout << "Number of Buttons: " << numberOfButtons << endl;

    if (detailed) {
        pair<double, double> metrics = computeAdditionalMetrics();
        cout << fixed << setprecision(2);
        cout << "Performance Score: " << metrics.first << endl;
        cout << "Value Score: " << metrics.second << endl;
    }
    cout << "----------------------------------------" << endl;
}

pair<double, double> Mouse::computeAdditionalMetrics() const {
    double performance = (pollingRate / 100.0) * 5.0;
    performance += numberOfButtons * 5.0;

    if (connectivityType == "Wireless" || connectivityType == "Both") performance += 10;
    else if (connectivityType == "Wired") performance += 5;

    double valueScore = (price > 0) ? performance / price : 0;
    return {performance, valueScore};
}

double Mouse::getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const {
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double performance = metrics.first;

    if (budgetCategory == "low" && price > 50) return 1.0; 
    if (budgetCategory == "medium" && (price < 25 || price > 100)) return 1.0; 
    if (budgetCategory == "high" && price < 70) return 1.0; 

    compatibilityScore += performance * 0.3;

    if (budgetCategory == "low" && price < 30) compatibilityScore += 30;
    else if (budgetCategory == "medium" && price >= 25 && price < 80) compatibilityScore += 30;
    else if (budgetCategory == "high" && price >= 70) compatibilityScore += 30;
    else compatibilityScore += 5;

    string userPreference = "";
    if (preferences.count("Peripheral")) {
        userPreference = preferences.at("Peripheral");
    }

    if (!userPreference.empty() && brand.find(userPreference) != string::npos) {
        compatibilityScore += 15;
    } else {
        compatibilityScore += 5;
    }

    double maxPossibleScore = (470 * 0.3) + 30 + 15;
     if(maxPossibleScore <= 0) return 0;

    compatibilityScore = (compatibilityScore / maxPossibleScore) * 100.0;

    return min(max(compatibilityScore, 0.0), 100.0);
}

string Mouse::getTypeString() const {
    return "Mouse";
}

void Mouse::writeDataToStream(ofstream& out) const {
     out << getTypeString() << ","
        << partID << ","
        << name << ","
        << price << ","
        << quantity << ","
        << brand << ","
        << connectivityType << ","
        << pollingRate << ","
        << weight << ","
        << numberOfButtons << endl;
} 
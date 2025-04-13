#include "Motherboard.h"
#include <iostream>
#include <iomanip>
#include <map> // For compatibility scoring

using namespace std;

void Motherboard::displayDetails(bool detailed) const {
    cout << "----------------------------------------" << endl;
    cout << "Type: Motherboard" << endl;
    cout << "ID: " << partID << endl;
    cout << "Name: " << name << endl;
    cout << fixed << setprecision(2);
    cout << "Price: $" << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Manufacturer: " << manufacturer << endl;
    cout << "Warranty: " << warrantyPeriod << " months" << endl;
    cout << "Chipset: " << chipset << endl;
    cout << "Form Factor: " << formFactor << endl;
    cout << "Socket: " << socket << endl;

    if (detailed) {
        pair<double, double> metrics = computeAdditionalMetrics();
        cout << fixed << setprecision(2);
        cout << "Feature Score: " << metrics.first << endl;
        cout << "Value Score: " << metrics.second << endl;
    }
    cout << "----------------------------------------" << endl;
}

pair<double, double> Motherboard::computeAdditionalMetrics() const {
    map<string, int> chipsetScores = {{"X670E", 10}, {"X670", 9}, {"B650E", 8}, {"B650", 7}, {"Z790", 10}, {"Z690", 9}, {"B760", 8}, {"B660", 7}};
    map<string, int> formFactorScores = {{"E-ATX", 5}, {"ATX", 4}, {"Micro-ATX", 3}, {"Mini-ITX", 2}};

    double featureScore = (chipsetScores.count(chipset) ? chipsetScores.at(chipset) : 5) * 10.0;
    featureScore += (formFactorScores.count(formFactor) ? formFactorScores.at(formFactor) : 2) * 5.0;

    double valueScore = (price > 0) ? featureScore / price : 0;
    return {featureScore, valueScore};
}

double Motherboard::getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const {
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double featureScore = metrics.first;

    if (budgetCategory == "low" && price > 150) return 1.0;
    if (budgetCategory == "medium" && (price < 80 || price > 300)) return 1.0;
    if (budgetCategory == "high" && price < 200) return 1.0;

    compatibilityScore += featureScore * 0.2;

    if (budgetCategory == "low" && price < 100) compatibilityScore += 30;
    else if (budgetCategory == "medium" && price >= 80 && price < 250) compatibilityScore += 30;
    else if (budgetCategory == "high" && price >= 200) compatibilityScore += 30;
    else compatibilityScore += 5;

    string userPreference = "";
    if (preferences.count("Motherboard")) { 
        userPreference = preferences.at("Motherboard");
    }
    
    if (!userPreference.empty() && manufacturer.find(userPreference) != string::npos) {
        compatibilityScore += 20;
    } else {
        compatibilityScore += 5;
    }

    double maxPossibleScore = (125 * 0.2) + 30 + 20;
     if(maxPossibleScore <= 0) return 0;

    compatibilityScore = (compatibilityScore / maxPossibleScore) * 100.0;

    return min(max(compatibilityScore, 0.0), 100.0);
}

string Motherboard::getTypeString() const {
    return "Motherboard";
}

void Motherboard::writeDataToStream(ofstream& out) const {
     out << getTypeString() << ","
        << partID << ","
        << name << ","
        << price << ","
        << quantity << ","
        << manufacturer << ","
        << warrantyPeriod << ","
        << chipset << ","
        << formFactor << ","
        << socket << endl;
} 
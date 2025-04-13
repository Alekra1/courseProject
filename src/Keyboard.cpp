#include "Keyboard.h"
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

void Keyboard::displayDetails(bool detailed) const {
    cout << "----------------------------------------" << endl;
    cout << "Type: Keyboard" << endl;
    cout << "ID: " << partID << endl;
    cout << "Name: " << name << endl;
    cout << fixed << setprecision(2);
    cout << "Price: $" << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Brand: " << brand << endl;
    cout << "Connectivity: " << connectivityType << endl;
    cout << "Switch Type: " << switchType << endl;
    cout << "Backlit: " << (backlit ? "Yes" : "No") << endl;
    cout << "Hot-Swappable: " << (isHotSwappable ? "Yes" : "No") << endl;

    if (detailed) {
        pair<double, double> metrics = computeAdditionalMetrics();
        cout << fixed << setprecision(2);
        cout << "Feature Score: " << metrics.first << endl;
        cout << "Value Score: " << metrics.second << endl;
    }
    cout << "----------------------------------------" << endl;
}

pair<double, double> Keyboard::computeAdditionalMetrics() const {
    map<string, int> switchScores = {{"Mechanical-Tactile", 10}, {"Mechanical-Linear", 9}, {"Mechanical-Clicky", 8}, {"Membrane", 5}, {"Optical", 10}};
    double featureScore = (switchScores.count(switchType) ? switchScores.at(switchType) : 6) * 5.0;
    featureScore += (backlit ? 15 : 5);
    featureScore += (isHotSwappable ? 20 : 5);

    if (connectivityType == "Wireless" || connectivityType == "Both") featureScore += 10;
    else if (connectivityType == "Wired") featureScore += 5;

    double valueScore = (price > 0) ? featureScore / price : 0;
    return {featureScore, valueScore};
}

double Keyboard::getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const {
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double featureScore = metrics.first;

    if (budgetCategory == "low" && price > 80) return 1.0;
    if (budgetCategory == "medium" && (price < 40 || price > 200)) return 1.0;
    if (budgetCategory == "high" && price < 100) return 1.0;

    compatibilityScore += featureScore * 0.3;

    if (budgetCategory == "low" && price < 50) compatibilityScore += 30;
    else if (budgetCategory == "medium" && price >= 40 && price < 150) compatibilityScore += 30;
    else if (budgetCategory == "high" && price >= 100) compatibilityScore += 30;
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

    double maxPossibleScore = (95 * 0.3) + 30 + 15;
     if(maxPossibleScore <= 0) return 0;

    compatibilityScore = (compatibilityScore / maxPossibleScore) * 100.0;

    return min(max(compatibilityScore, 0.0), 100.0);
}

string Keyboard::getTypeString() const {
    return "Keyboard";
}

void Keyboard::writeDataToStream(ofstream& out) const {
    out << getTypeString() << ","
        << partID << ","
        << name << ","
        << price << ","
        << quantity << ","
        << brand << ","
        << connectivityType << ","
        << switchType << ","
        << (backlit ? "true" : "false") << ","
        << (isHotSwappable ? "true" : "false") << endl;
} 
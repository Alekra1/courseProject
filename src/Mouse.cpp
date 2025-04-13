#include "Mouse.h"
#include <iostream>
#include <iomanip>
#include <cmath> // For min/max
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
    // Simple performance: higher polling rate and more buttons are better.
    // Weight preference is subjective, so we don't include it directly in performance,
    // but lower weight might be considered 'better' for competitive gaming.
    double performance = (pollingRate / 100.0) * 5.0; // Scale polling rate
    performance += numberOfButtons * 5.0; // Add points for buttons

    // Add points based on connectivity
    if (connectivityType == "Wireless" || connectivityType == "Both") performance += 10;
    else if (connectivityType == "Wired") performance += 5;

    double valueScore = (price > 0) ? performance / price : 0;
    return {performance, valueScore};
}

double Mouse::getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const {
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double performance = metrics.first;

    // --- Improved Budget Logic --- 
    if (budgetCategory == "low" && price > 50) return 1.0; 
    if (budgetCategory == "medium" && (price < 25 || price > 100)) return 1.0; 
    if (budgetCategory == "high" && price < 70) return 1.0; 
    // --- End Improved Budget Logic ---

    // Base score on performance/features
    compatibilityScore += performance * 0.3;

    // Adjust based on budget category
    if (budgetCategory == "low" && price < 30) compatibilityScore += 30;
    else if (budgetCategory == "medium" && price >= 25 && price < 80) compatibilityScore += 30;
    else if (budgetCategory == "high" && price >= 70) compatibilityScore += 30;
    else compatibilityScore += 5;

    // Adjust based on brand preference
    string userPreference = "";
    if (preferences.count("Peripheral")) {
        userPreference = preferences.at("Peripheral");
    }

    if (!userPreference.empty() && brand.find(userPreference) != string::npos) {
        compatibilityScore += 15;
    } else {
        compatibilityScore += 5;
    }

    // Normalize (Max performance: (8000/100)*5 + 12*5 + 10 = 400 + 60 + 10 = 470)
    double maxPossibleScore = (470 * 0.3) + 30 + 15; // 141 + 30 + 15 = 186
     if(maxPossibleScore <= 0) return 0; // Avoid division by zero

    compatibilityScore = (compatibilityScore / maxPossibleScore) * 100.0;

    return min(max(compatibilityScore, 0.0), 100.0); // Clamp score
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
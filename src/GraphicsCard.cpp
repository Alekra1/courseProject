#include "GraphicsCard.h"
#include <iostream>
#include <iomanip>
#include <cmath> // For score calculation, if needed
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
    // Simplified performance: weighted sum of memory size and clocks
    double performance = (memorySize * 50.0) + (coreClock * 0.1) + (memoryClock * 0.05);
    double pricePerformanceRatio = (price > 0) ? performance / price : 0;
    return {performance, pricePerformanceRatio};
}

double GraphicsCard::getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const {
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double performance = metrics.first;

    // --- Improved Budget Logic --- 
    // If price is drastically outside the budget category, return a very low score.
    if (budgetCategory == "low" && price > 300) return 1.0; // Significantly over low budget
    if (budgetCategory == "medium" && (price < 150 || price > 800)) return 1.0; // Significantly outside medium budget
    if (budgetCategory == "high" && price < 400) return 1.0; // Significantly under high budget (less likely an issue, but could be)
    // --- End Improved Budget Logic ---

    // Base score on performance (adjust weighting as needed)
    compatibilityScore += performance * 0.05; // Scale performance contribution

    // Adjust based on budget category (refined ranges)
    if (budgetCategory == "low" && price < 200) compatibilityScore += 30; // Strong bonus
    else if (budgetCategory == "medium" && price >= 150 && price < 600) compatibilityScore += 30;
    else if (budgetCategory == "high" && price >= 500) compatibilityScore += 30;
    else compatibilityScore += 5; // Minor bonus if within acceptable range but not ideal

    // Adjust based on manufacturer preference
    string userPreference = "";
    if (preferences.count("GPU")) {
        userPreference = preferences.at("GPU");
    }

    if (!userPreference.empty() && manufacturer.find(userPreference) != string::npos) {
        compatibilityScore += 20; // Bonus for matching preferred manufacturer
    } else {
        compatibilityScore += 5; // Small bonus if no specific preference or mismatch
    }

    // Normalize (heuristic, needs tuning based on expected performance scores)
    // Example: Max theoretical score could be (32*50 + 2500*0.1 + 20000*0.05)*0.05 + 40 + 20 = 142.5 + 40 + 20 = 202.5
    double maxPossibleScore = ((16 * 50.0) + (2000 * 0.1) + (18000 * 0.05)) * 0.05 + 40 + 20; // Example max score for normalization
     if(maxPossibleScore <= 0) return 0; // Avoid division by zero

    compatibilityScore = (compatibilityScore / maxPossibleScore) * 100.0;

    return min(max(compatibilityScore, 0.0), 100.0); // Clamp score
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
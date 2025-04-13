#include "GraphicsCard.h"
#include <iostream>
#include <iomanip>
#include <cmath> // For score calculation, if needed

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

double GraphicsCard::getCompatibilityRate(const string& userPreference, const string& budgetCategory) const {
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double performance = metrics.first;

    // Base score on performance (adjust weighting as needed)
    compatibilityScore += performance * 0.05; // Scale performance contribution

    // Adjust based on budget category
    if (budgetCategory == "low" && price < 200) compatibilityScore += 20;
    else if (budgetCategory == "medium" && price >= 200 && price < 600) compatibilityScore += 30;
    else if (budgetCategory == "high" && price >= 600) compatibilityScore += 40;
    else compatibilityScore += 10; // Generic budget adjustment

    // Adjust based on manufacturer preference
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
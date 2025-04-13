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
        cout << "Feature Score: " << metrics.first << endl; // Renamed for clarity
        cout << "Value Score: " << metrics.second << endl; // Renamed for clarity
    }
    cout << "----------------------------------------" << endl;
}

pair<double, double> Motherboard::computeAdditionalMetrics() const {
    // Simplified feature score: based on chipset and form factor importance (heuristic)
    map<string, int> chipsetScores = {{"X670E", 10}, {"X670", 9}, {"B650E", 8}, {"B650", 7}, {"Z790", 10}, {"Z690", 9}, {"B760", 8}, {"B660", 7}}; // Example scores
    map<string, int> formFactorScores = {{"E-ATX", 5}, {"ATX", 4}, {"Micro-ATX", 3}, {"Mini-ITX", 2}};
    
    double featureScore = (chipsetScores.count(chipset) ? chipsetScores.at(chipset) : 5) * 10.0; // Base score 5 if chipset not found
    featureScore += (formFactorScores.count(formFactor) ? formFactorScores.at(formFactor) : 2) * 5.0; // Base score 2 if form factor not found

    double valueScore = (price > 0) ? featureScore / price : 0;
    return {featureScore, valueScore};
}

double Motherboard::getCompatibilityRate(const string& userPreference, const string& budgetCategory) const {
    // Motherboard compatibility is complex. This is a simplified placeholder.
    // Real compatibility depends heavily on CPU socket, RAM type/speed, PCIe slots, etc.
    // For this project, we'll focus on budget and manufacturer preference primarily.
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double featureScore = metrics.first;

    // Base score on features (lower weight compared to CPU/GPU performance)
    compatibilityScore += featureScore * 0.2; 

    // Adjust based on budget category
    if (budgetCategory == "low" && price < 100) compatibilityScore += 25;
    else if (budgetCategory == "medium" && price >= 100 && price < 250) compatibilityScore += 35;
    else if (budgetCategory == "high" && price >= 250) compatibilityScore += 45;
    else compatibilityScore += 15; // Generic budget adjustment

    // Adjust based on manufacturer preference
    if (!userPreference.empty() && manufacturer.find(userPreference) != string::npos) {
        compatibilityScore += 20; // Bonus for matching preferred manufacturer
    } else {
        compatibilityScore += 5; // Small bonus
    }
    
    // Normalize (heuristic, max feature score is roughly 10*10 + 5*5 = 125)
    double maxPossibleScore = (125 * 0.2) + 45 + 20; // 25 + 45 + 20 = 90
     if(maxPossibleScore <= 0) return 0; // Avoid division by zero

    compatibilityScore = (compatibilityScore / maxPossibleScore) * 100.0;

    return min(max(compatibilityScore, 0.0), 100.0); // Clamp score
} 
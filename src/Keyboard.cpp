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
    map<string, int> switchScores = {{"Mechanical-Tactile", 10}, {"Mechanical-Linear", 9}, {"Mechanical-Clicky", 8}, {"Membrane", 5}, {"Optical", 10}}; // Example scores
    double featureScore = (switchScores.count(switchType) ? switchScores.at(switchType) : 6) * 5.0; // Base score 6
    featureScore += (backlit ? 15 : 5); // Bonus for backlight
    featureScore += (isHotSwappable ? 20 : 5); // Bonus for hot-swappable
    
    // Add points based on connectivity
    if (connectivityType == "Wireless" || connectivityType == "Both") featureScore += 10;
    else if (connectivityType == "Wired") featureScore += 5;

    double valueScore = (price > 0) ? featureScore / price : 0;
    return {featureScore, valueScore};
}

double Keyboard::getCompatibilityRate(const string& userPreference, const string& budgetCategory) const {
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double featureScore = metrics.first;

    // Base score on features
    compatibilityScore += featureScore * 0.3; // Features are important for peripherals

    // Adjust based on budget category
    if (budgetCategory == "low" && price < 50) compatibilityScore += 25;
    else if (budgetCategory == "medium" && price >= 50 && price < 150) compatibilityScore += 35;
    else if (budgetCategory == "high" && price >= 150) compatibilityScore += 40;
    else compatibilityScore += 15;

    // Adjust based on brand preference (less critical than internal components usually)
    if (!userPreference.empty() && brand.find(userPreference) != string::npos) {
        compatibilityScore += 15; // Lower bonus for brand match
    } else {
        compatibilityScore += 5;
    }

    // Normalize (Max feature score: (10*5 + 15 + 20 + 10) = 95)
    double maxPossibleScore = (95 * 0.3) + 40 + 15; // 28.5 + 40 + 15 = 83.5
     if(maxPossibleScore <= 0) return 0; // Avoid division by zero

    compatibilityScore = (compatibilityScore / maxPossibleScore) * 100.0;

    return min(max(compatibilityScore, 0.0), 100.0); // Clamp score
} 
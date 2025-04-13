#include "Processor.h"
#include <iostream>
#include <iomanip>
#include <cmath>

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

double Processor::getCompatibilityRate(const string& userPreference, const string& budgetCategory) const {
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double performance = metrics.first;
    double pricePerformanceRatio = metrics.second;

    // Base score on performance
    compatibilityScore += performance * 0.5; // Performance is 50% of the score

    // Adjust based on budget category
    if (budgetCategory == "low" && price < 150) compatibilityScore += 20;
    else if (budgetCategory == "medium" && price >= 150 && price < 400) compatibilityScore += 30;
    else if (budgetCategory == "high" && price >= 400) compatibilityScore += 40;
    else compatibilityScore += 10; // Generic budget adjustment

    // Adjust based on manufacturer preference (userPreference might contain preferred manufacturer)
    if (!userPreference.empty() && manufacturer.find(userPreference) != string::npos) {
        compatibilityScore += 20; // Bonus for matching preferred manufacturer
    } else {
        compatibilityScore += 5; // Small bonus if no specific preference or mismatch
    }

    // Normalize the score to be out of 100 (this is a heuristic, adjust max score based on expected ranges)
    double maxPossibleScore = (coreCount * clockSpeed * 0.5) + 40 + 20; // Theoretical max, adjust as needed
    if(maxPossibleScore <= 0) return 0; // Avoid division by zero
    
    compatibilityScore = (compatibilityScore / maxPossibleScore) * 100.0;


    return min(max(compatibilityScore, 0.0), 100.0); // Clamp score between 0 and 100
} 
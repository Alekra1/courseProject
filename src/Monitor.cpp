#include "Monitor.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream> // For splitting resolution string
#include <map>

using namespace std;

// Helper to get resolution width/height
pair<int, int> parseResolution(const string& res) {
    stringstream ss(res);
    string segment;
    int width = 0, height = 0;
    if (getline(ss, segment, 'x')) {
        try { width = stoi(segment); } catch (...) { /* ignore */ }
    }
    if (getline(ss, segment, 'x')) {
        try { height = stoi(segment); } catch (...) { /* ignore */ }
    }
    return {width, height};
}

void Monitor::displayDetails(bool detailed) const {
    cout << "----------------------------------------" << endl;
    cout << "Type: Monitor" << endl;
    cout << "ID: " << partID << endl;
    cout << "Name: " << name << endl;
    cout << fixed << setprecision(2);
    cout << "Price: $" << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Brand: " << brand << endl;
    cout << "Connectivity: " << connectivityType << endl; // Assuming this exists in Peripheral base
    cout << fixed << setprecision(1);
    cout << "Screen Size: " << screenSize << " inches" << endl;
    cout << "Resolution: " << resolution << endl;
    cout << "Refresh Rate: " << refreshRate << " Hz" << endl;
    cout << "Panel Type: " << panelType << endl;

    if (detailed) {
        pair<double, double> metrics = computeAdditionalMetrics();
        cout << fixed << setprecision(2);
        cout << "Performance Score: " << metrics.first << endl;
        cout << "Value Score: " << metrics.second << endl;
    }
    cout << "----------------------------------------" << endl;
}

pair<double, double> Monitor::computeAdditionalMetrics() const {
    pair<int, int> resWH = parseResolution(resolution);
    int width = resWH.first;
    int height = resWH.second;
    double pixelCount = width * height;

    map<string, int> panelScores = {{"OLED", 10}, {"IPS", 8}, {"VA", 7}, {"TN", 5}}; // Example scores

    // Performance score based on resolution, refresh rate, and panel type
    double performance = (pixelCount / 100000.0) * 0.5; // Scale pixel count
    performance += (refreshRate / 60.0) * 10.0; // Scale refresh rate (base 60Hz)
    performance += (panelScores.count(panelType) ? panelScores.at(panelType) : 6) * 5.0; // Base score 6

    double valueScore = (price > 0) ? performance / price : 0;
    return {performance, valueScore};
}

double Monitor::getCompatibilityRate(const string& userPreference, const string& budgetCategory) const {
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double performance = metrics.first;

    // Base score on performance
    compatibilityScore += performance * 0.25; // Monitor performance matters

    // Adjust based on budget category
    if (budgetCategory == "low" && price < 150) compatibilityScore += 25;
    else if (budgetCategory == "medium" && price >= 150 && price < 400) compatibilityScore += 35;
    else if (budgetCategory == "high" && price >= 400) compatibilityScore += 40;
    else compatibilityScore += 15;

    // Adjust based on brand preference
    if (!userPreference.empty() && brand.find(userPreference) != string::npos) {
        compatibilityScore += 15;
    } else {
        compatibilityScore += 5;
    }

    // Normalize (Max performance: (8M/100k)*0.5 + (360/60)*10 + 10*5 = 40 + 60 + 50 = 150)
    double maxPossibleScore = (150 * 0.25) + 40 + 15; // 37.5 + 40 + 15 = 92.5
     if(maxPossibleScore <= 0) return 0; // Avoid division by zero

    compatibilityScore = (compatibilityScore / maxPossibleScore) * 100.0;

    return min(max(compatibilityScore, 0.0), 100.0); // Clamp score
} 
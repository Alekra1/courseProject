#include "Monitor.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <cmath>

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
    cout << "Connectivity: " << connectivityType << endl;
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

    map<string, int> panelScores = {{"OLED", 10}, {"IPS", 8}, {"VA", 7}, {"TN", 5}};

    double performance = (pixelCount / 100000.0) * 0.5;
    performance += (refreshRate / 60.0) * 10.0; 
    performance += (panelScores.count(panelType) ? panelScores.at(panelType) : 6) * 5.0;

    double valueScore = (price > 0) ? performance / price : 0;
    return {performance, valueScore};
}

double Monitor::getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const {
    double compatibilityScore = 0.0;
    pair<double, double> metrics = computeAdditionalMetrics();
    double performance = metrics.first;

    if (budgetCategory == "low" && price > 250) return 1.0; 
    if (budgetCategory == "medium" && (price < 100 || price > 600)) return 1.0; 
    if (budgetCategory == "high" && price < 300) return 1.0; 

    compatibilityScore += performance * 0.25;

    if (budgetCategory == "low" && price < 150) compatibilityScore += 30;
    else if (budgetCategory == "medium" && price >= 100 && price < 400) compatibilityScore += 30;
    else if (budgetCategory == "high" && price >= 300) compatibilityScore += 30;
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

    double maxPossibleScore = (150 * 0.25) + 30 + 15;
     if(maxPossibleScore <= 0) return 0;

    compatibilityScore = (compatibilityScore / maxPossibleScore) * 100.0;

    return min(max(compatibilityScore, 0.0), 100.0);
}

string Monitor::getTypeString() const {
    return "Monitor";
}

void Monitor::writeDataToStream(ofstream& out) const {
    out << getTypeString() << ","
        << partID << ","
        << name << ","
        << price << ","
        << quantity << ","
        << brand << ","
        << connectivityType << ","
        << screenSize << ","
        << resolution << ","
        << refreshRate << ","
        << panelType << endl;
} 
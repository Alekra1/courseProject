#include "Processor.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::pair;

void Processor::displayDetails(bool detailed) {
    // Display basic information
    cout << "Processor: " << getName() << endl;
    cout << "Part ID: " << getPartID() << endl;
    cout << "Price: $" << fixed << setprecision(2) << getPrice() << endl;
    cout << "Quantity in stock: " << getQuantity() << endl;

    if (detailed) {
        // Display detailed information
        cout << "Manufacturer: " << getManufacturer() << endl;
        cout << "Warranty Period: " << getWarrantyPeriod() << " months" << endl;
        cout << "Clock Speed: " << clockSpeed << " GHz" << endl;
        cout << "Core Count: " << coreCount << endl;
        cout << "Socket Type: " << socketType << endl;

        // Display computed metrics
        auto metrics = computeAdditionalMetrics();
        cout << "Performance Score: " << metrics.first << endl;
        cout << "Price-Performance Ratio: " << metrics.second << endl;
    }
}

pair<double, double> Processor::computeAdditionalMetrics() {
    // Calculate performance score based on clock speed and core count
    double performance = clockSpeed * coreCount;

    // Calculate price-performance ratio (lower is better)
    double pricePerPerformance = getPrice() / performance;

    return {performance, pricePerPerformance};
}

double Processor::getCompatibilityRate(const string& userPreference, const string& budgetCategory) {
    double compatibility = 0.0;
    
    // Check manufacturer preference
    if (userPreference == getManufacturer()) {
        compatibility += 40.0;  // 40% weight for manufacturer preference
    }

    // Check budget category
    if (budgetCategory == "high" && getPrice() > 300) {
        compatibility += 30.0;  // 30% weight for high-end budget
    } else if (budgetCategory == "medium" && getPrice() > 150 && getPrice() <= 300) {
        compatibility += 30.0;  // 30% weight for medium budget
    } else if (budgetCategory == "low" && getPrice() <= 150) {
        compatibility += 30.0;  // 30% weight for low budget
    }

    // Performance score contribution (30% weight)
    auto metrics = computeAdditionalMetrics();
    double performanceScore = metrics.first;
    double maxPerformance = 100.0;  // Assuming this is a reasonable maximum
    compatibility += (performanceScore / maxPerformance) * 30.0;

    return compatibility;
} 
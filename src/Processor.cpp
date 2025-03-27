#include "Processor.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::pair;

void Processor::displayDetails(bool detailed) {
    cout << "Processor: " << getName() << endl;
    cout << "Part ID: " << getPartID() << endl;
    cout << "Price: $" << fixed << setprecision(2) << getPrice() << endl;
    cout << "Quantity in stock: " << getQuantity() << endl;

    if (detailed) {
        cout << "Manufacturer: " << getManufacturer() << endl;
        cout << "Warranty Period: " << getWarrantyPeriod() << " months" << endl;
        cout << "Clock Speed: " << clockSpeed << " GHz" << endl;
        cout << "Core Count: " << coreCount << endl;
        cout << "Socket Type: " << socketType << endl;

        auto metrics = computeAdditionalMetrics();
        cout << "Performance Score: " << metrics.first << endl;
        cout << "Price-Performance Ratio: " << metrics.second << endl;
    }
}

pair<double, double> Processor::computeAdditionalMetrics() {
    double performance = clockSpeed * coreCount;
    double pricePerPerformance = getPrice() / performance;
    return {performance, pricePerPerformance};
}

double Processor::getCompatibilityRate(const string& userPreference, const string& budgetCategory) {
    double compatibility = 0.0;
    
    if (userPreference == getManufacturer()) {
        compatibility += 40.0;
    }

    if (budgetCategory == "high" && getPrice() > 300) {
        compatibility += 30.0;
    } else if (budgetCategory == "medium" && getPrice() > 150 && getPrice() <= 300) {
        compatibility += 30.0;
    } else if (budgetCategory == "low" && getPrice() <= 150) {
        compatibility += 30.0;
    }

    auto metrics = computeAdditionalMetrics();
    double performanceScore = metrics.first;
    double maxPerformance = 100.0;
    compatibility += (performanceScore / maxPerformance) * 30.0;

    return compatibility;
} 
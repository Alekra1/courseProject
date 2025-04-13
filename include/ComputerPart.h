#ifndef COMPUTERPART_H
#define COMPUTERPART_H

#include <string>
#include <utility>
#include <iostream>
#include <fstream> // For ofstream in writeDataToStream
#include <vector> // Included for use in derived classes potentially
#include <map> // For preferences map

using namespace std;

class ComputerPart {
protected:
    string partID;
    string name;
    double price;
    int quantity;

public:
    ComputerPart(string id, string n, double p, int q)
        : partID(id), name(n), price(p), quantity(q) {}

    virtual ~ComputerPart() = default;

    virtual void displayDetails(bool detailed = false) const = 0;
    virtual pair<double, double> computeAdditionalMetrics() const = 0;
    virtual double getCompatibilityRate(const map<string, string>& preferences, const string& budgetCategory) const = 0;
    virtual string getTypeString() const = 0;
    virtual void writeDataToStream(ofstream& out) const = 0;

    void updateStock(int changeQuantity);

    string getPartID() const { return partID; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void setPrice(double newPrice) { if (newPrice >= 0) price = newPrice; }
};

#endif 
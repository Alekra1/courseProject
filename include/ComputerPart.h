#ifndef COMPUTER_PART_H
#define COMPUTER_PART_H

#include <string>
#include <utility>

using std::string;
using std::pair;

class ComputerPart {
protected:
    string partID;
    string name;
    double price;
    int quantity;

public:
    // Constructor
    ComputerPart(const string& id, const string& n, double p, int q)
        : partID(id), name(n), price(p), quantity(q) {}

    // Virtual destructor
    virtual ~ComputerPart() = default;

    // Pure virtual methods that must be implemented by derived classes
    virtual void displayDetails(bool detailed = false) = 0;
    virtual pair<double, double> computeAdditionalMetrics() = 0;
    virtual double getCompatibilityRate(const string& userPreference, const string& budgetCategory) = 0;

    // Concrete method for updating stock
    void updateStock(int newQuantity) {
        quantity = newQuantity;
    }

    // Getters
    string getPartID() const { return partID; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
};

#endif // COMPUTER_PART_H 
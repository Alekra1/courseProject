#ifndef INVENTORY_H
#define INVENTORY_H

#include "ComputerPart.h"
#include <vector>
#include <string>
#include <functional> // For std::function

using namespace std;

class Inventory {
private:
    vector<ComputerPart*> parts;
    string dataFilePath;

    // Private helper for quicksort partition
    int partition(int low, int high, function<bool(const ComputerPart*, const ComputerPart*)> lessThan);
    // Private helper for quicksort recursive step
    void quickSortRecursive(int low, int high, function<bool(const ComputerPart*, const ComputerPart*)> lessThan);

    // Private helper for binary search recursive step
    ComputerPart* binarySearchRecursive(const string& key, int low, int high, function<int(const ComputerPart*, const string&)> compare);

public:
    Inventory(const string& filePath);
    ~Inventory();

    void loadInventory();
    void saveInventory() const;

    void addPart(ComputerPart* part);
    bool removePart(const string& partID);
    ComputerPart* findPartById(const string& partID); // Uses binary search after sorting by ID
    ComputerPart* findPartByName(const string& name); // Uses binary search after sorting by Name

    void sortInventory(const string& sortBy); // "id", "name", "price", "performance"

    void displayInventory(bool detailed = false) const;

    const vector<ComputerPart*>& getParts() const { return parts; } // Allow read-only access
};

#endif // INVENTORY_H 
#ifndef INVENTORY_H
#define INVENTORY_H

#include "ComputerPart.h"
#include <vector>
#include <string>
#include <functional>

using namespace std;

class Inventory {
private:
    vector<ComputerPart*> parts;
    string dataFilePath;

    int partition(int low, int high, function<bool(const ComputerPart*, const ComputerPart*)> lessThan);
    void quickSortRecursive(int low, int high, function<bool(const ComputerPart*, const ComputerPart*)> lessThan);
    ComputerPart* binarySearchRecursive(const string& key, int low, int high, function<int(const ComputerPart*, const string&)> compare);

public:
    Inventory(const string& filePath);
    ~Inventory();

    void loadInventory();
    void saveInventory() const;

    void addPart(ComputerPart* part);
    bool removePart(const string& partID);
    ComputerPart* findPartById(const string& partID);
    ComputerPart* findPartByName(const string& name);

    void sortInventory(const string& sortBy);

    void displayInventory(bool detailed = false) const;

    const vector<ComputerPart*>& getParts() const { return parts; }
};

#endif 
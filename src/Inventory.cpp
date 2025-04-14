#include "Inventory.h"
#include "Processor.h"
#include "GraphicsCard.h"
#include "Motherboard.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Monitor.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <functional>
#include <limits>
#include <ios>
#include <iomanip> 

using namespace std;

Inventory::Inventory(const string& filePath) : dataFilePath(filePath) {
    loadInventory();
}

Inventory::~Inventory() {
    for (ComputerPart* part : parts) {
        delete part;
    }
    parts.clear();
}

// --- File I/O ---
void Inventory::loadInventory() {
    ifstream inputFile(dataFilePath);
    if (!inputFile.is_open()) {
        cerr << "Warning: Could not open inventory file: " << dataFilePath << ". Starting with empty inventory." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        string segment;
        vector<string> data;
        while (getline(ss, segment, ',')) {
            segment.erase(0, segment.find_first_not_of(" \t\n\r\f\v"));
            segment.erase(segment.find_last_not_of(" \t\n\r\f\v") + 1);
            data.push_back(segment);
        }

        if (data.empty()) continue;

        string type = data[0];
        try {
            if (data.size() < 5) throw runtime_error("Insufficient common data");
            string id = data[1];
            string name = data[2];
            double price = stod(data[3]);
            int quantity = stoi(data[4]);

            ComputerPart* newPart = nullptr;

            if (type == "Processor") {
                if (data.size() < 10) throw runtime_error("Insufficient Processor data");
                string mfr = data[5];
                int warranty = stoi(data[6]);
                double clock = stod(data[7]);
                int cores = stoi(data[8]);
                string socket = data[9];
                newPart = new Processor(id, name, price, quantity, mfr, warranty, clock, cores, socket);
            } else if (type == "GraphicsCard") {
                if (data.size() < 10) throw runtime_error("Insufficient GraphicsCard data");
                string mfr = data[5];
                int warranty = stoi(data[6]);
                int memSize = stoi(data[7]);
                double coreClk = stod(data[8]);
                double memClk = stod(data[9]);
                newPart = new GraphicsCard(id, name, price, quantity, mfr, warranty, memSize, coreClk, memClk);
            } else if (type == "Motherboard") {
                 if (data.size() < 10) throw runtime_error("Insufficient Motherboard data");
                 string mfr = data[5];
                 int warranty = stoi(data[6]);
                 string chip = data[7];
                 string form = data[8];
                 string socket = data[9];
                 newPart = new Motherboard(id, name, price, quantity, mfr, warranty, chip, form, socket);
            } else if (type == "Keyboard") {
                if (data.size() < 10) throw runtime_error("Insufficient Keyboard data");
                string brand = data[5];
                string conn = data[6];
                string switchT = data[7];
                bool backlit = (data[8] == "true" || data[8] == "1");
                bool hotSwap = (data[9] == "true" || data[9] == "1");
                newPart = new Keyboard(id, name, price, quantity, brand, conn, switchT, backlit, hotSwap);
            } else if (type == "Mouse") {
                if (data.size() < 10) throw runtime_error("Insufficient Mouse data");
                string brand = data[5];
                string conn = data[6];
                int poll = stoi(data[7]);
                double weight = stod(data[8]);
                int buttons = stoi(data[9]);
                newPart = new Mouse(id, name, price, quantity, brand, conn, poll, weight, buttons);
            } else if (type == "Monitor") {
                if (data.size() < 11) throw runtime_error("Insufficient Monitor data");
                string brand = data[5];
                string conn = data[6];
                double size = stod(data[7]);
                string res = data[8];
                int refresh = stoi(data[9]);
                string panel = data[10];
                newPart = new Monitor(id, name, price, quantity, brand, conn, size, res, refresh, panel);
            } else {
                cerr << "Warning: Unknown part type '<" << type << ">' in inventory file. Skipping line." << endl;
            }

            if (newPart) {
                parts.push_back(newPart);
            }
        } catch (const exception& e) {
            cerr << "Error parsing line: " << line << " -> " << e.what() << endl;
        }
    }
    inputFile.close();
}

void Inventory::saveInventory() const {
    ofstream outputFile(dataFilePath);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open inventory file for writing: " << dataFilePath << endl;
        return;
    }
    outputFile << fixed << setprecision(2);
    for (const ComputerPart* part : parts) {
        part->writeDataToStream(outputFile);
    }
    outputFile.close();
}

// --- Inventory Management ---
void Inventory::addPart(ComputerPart* part) {
    if (!part) return;
    auto it = find_if(parts.begin(), parts.end(),
                       [&](const ComputerPart* p){ return p->getPartID() == part->getPartID(); });
    if (it != parts.end()) {
        cerr << "Warning: Part with ID " << part->getPartID() << " already exists. Not adding." << endl;
        delete part;
        return;
    }
    parts.push_back(part);
}

bool Inventory::removePart(const string& partID) {
    auto it = remove_if(parts.begin(), parts.end(),
                         [&](ComputerPart* p){ 
                             if (p->getPartID() == partID) {
                                 delete p;
                                 return true;
                             }
                             return false;
                         });
    bool removed = (it != parts.end());
    if (removed) {
        parts.erase(it, parts.end());
    }
    return removed;
}

// --- Sorting (Quicksort Implementation) ---
int Inventory::partition(int low, int high, function<bool(const ComputerPart*, const ComputerPart*)> lessThan) {
    ComputerPart* pivot = parts[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (lessThan(parts[j], pivot)) {
            i++;
            swap(parts[i], parts[j]);
        }
    }
    swap(parts[i + 1], parts[high]);
    return (i + 1);
}

void Inventory::quickSortRecursive(int low, int high, function<bool(const ComputerPart*, const ComputerPart*)> lessThan) {
    if (low < high) {
        int pi = partition(low, high, lessThan);
        quickSortRecursive(low, pi - 1, lessThan);
        quickSortRecursive(pi + 1, high, lessThan);
    }
}

void Inventory::sortInventory(const string& sortBy) {
    if (parts.empty()) return;

    function<bool(const ComputerPart*, const ComputerPart*)> comparator;

    if (sortBy == "id") {
        comparator = [](const ComputerPart* a, const ComputerPart* b) {
            return a->getPartID() < b->getPartID();
        };
    } else if (sortBy == "name") {
        comparator = [](const ComputerPart* a, const ComputerPart* b) {
            return a->getName() < b->getName();
        };
    } else if (sortBy == "price") {
        comparator = [](const ComputerPart* a, const ComputerPart* b) {
            return a->getPrice() < b->getPrice();
        };
    } else if (sortBy == "performance") {
        comparator = [](const ComputerPart* a, const ComputerPart* b) {
            return a->computeAdditionalMetrics().first > b->computeAdditionalMetrics().first; // Higher performance first
        };
    } else {
        cerr << "Warning: Unknown sort criteria: " << sortBy << ". Sorting by ID instead." << endl;
        comparator = [](const ComputerPart* a, const ComputerPart* b) {
            return a->getPartID() < b->getPartID();
        };
    }

    quickSortRecursive(0, parts.size() - 1, comparator);
}

// --- Searching (Binary Search Implementation) ---
ComputerPart* Inventory::binarySearchRecursive(const string& key, int low, int high, function<int(const ComputerPart*, const string&)> compare) {
    if (high >= low) {
        int mid = low + (high - low) / 2;
        int comparisonResult = compare(parts[mid], key);

        if (comparisonResult == 0) {
            return parts[mid]; // Key found
        }
        if (comparisonResult > 0) { // parts[mid] > key
            return binarySearchRecursive(key, low, mid - 1, compare);
        }
        // comparisonResult < 0 // parts[mid] < key
        return binarySearchRecursive(key, mid + 1, high, compare);
    }
    return nullptr; // Key not found
}

ComputerPart* Inventory::findPartById(const string& partID) {
    sortInventory("id"); // Binary search requires sorted data
    function<int(const ComputerPart*, const string&)> compareById = 
        [](const ComputerPart* p, const string& id) {
            if (p->getPartID() == id) return 0;
            if (p->getPartID() < id) return -1;
            return 1;
        };
    return binarySearchRecursive(partID, 0, parts.size() - 1, compareById);
}

ComputerPart* Inventory::findPartByName(const string& name) {
    sortInventory("name"); // Binary search requires sorted data
     function<int(const ComputerPart*, const string&)> compareByName = 
        [](const ComputerPart* p, const string& n) {
            if (p->getName() == n) return 0;
            if (p->getName() < n) return -1;
            return 1;
        };
    return binarySearchRecursive(name, 0, parts.size() - 1, compareByName);
}

// --- Display Inventory ---
void Inventory::displayInventory(bool detailed) const {
    if (parts.empty()) {
        cout << "Inventory is empty." << endl;
        return;
    }
    cout << "\n--- Current Inventory --- (" << parts.size() << " items)" << endl;
    for (const auto* part : parts) {
        part->displayDetails(detailed);
    }
    cout << "--- End of Inventory ---\n" << endl;
}
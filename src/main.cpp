#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <ios>
#include <memory> // For unique_ptr if needed, though raw pointers are used in Inventory
#include <algorithm> // For std::sort with compatibility scores
#include <iomanip> // For setprecision

#include "Inventory.h"
#include "ComputerPart.h"
// Include headers for all concrete part types for adding new parts
#include "Processor.h"
#include "GraphicsCard.h"
#include "Motherboard.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Monitor.h"

using namespace std;

// --- Helper Functions --- 

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getValidatedInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    // Basic validation: remove leading/trailing whitespace
    input.erase(0, input.find_first_not_of(" \t\n\r\f\v"));
    input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1);
    return input;
}

double getValidatedDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        } else {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            clearInputBuffer();
        }
    }
}

int getValidatedInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        } else {
            cout << "Invalid input. Please enter an integer." << endl;
            cin.clear();
            clearInputBuffer();
        }
    }
}

bool getValidatedBool(const string& prompt) {
    string input;
    while (true) {
        input = getValidatedInput(prompt + " (yes/no): ");
        if (input == "yes" || input == "y") return true;
        if (input == "no" || input == "n") return false;
        cout << "Invalid input. Please enter 'yes' or 'no'." << endl;
    }
}

string getBudgetCategory(double budget) {
    if (budget < 800) return "low";
    if (budget < 1500) return "medium";
    return "high";
}

// --- Menu Functions --- 

void displayMainMenu() {
    cout << "\n--- Main Menu ---" << endl;
    cout << "1. Login as Customer" << endl;
    cout << "2. Login as Staff" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

void displayCustomerMenu() {
    cout << "\n--- Customer Menu ---" << endl;
    cout << "1. Find Recommended Build" << endl;
    cout << "2. Browse All Parts" << endl;
    cout << "3. Search Part by ID" << endl;
    cout << "4. Search Part by Name" << endl;
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";
}

void displayStaffMenu() {
    cout << "\n--- Staff Menu ---" << endl;
    cout << "1. Display Inventory (Summary)" << endl;
    cout << "2. Display Inventory (Detailed)" << endl;
    cout << "3. Add New Part" << endl;
    cout << "4. Remove Part by ID" << endl;
    cout << "5. Update Part Stock" << endl;
    cout << "6. Search Part by ID" << endl;
    cout << "7. Search Part by Name" << endl;
    cout << "8. Sort Inventory" << endl;
    cout << "9. Save Inventory to File" << endl;
    cout << "0. Logout" << endl;
    cout << "Enter your choice: ";
}

// --- Staff Actions --- 

void handleAddPart(Inventory& inventory) {
    cout << "\n--- Add New Part ---" << endl;
    cout << "Select Part Type:" << endl;
    cout << "1. Processor  2. Graphics Card  3. Motherboard" << endl;
    cout << "4. Keyboard   5. Mouse          6. Monitor" << endl;
    int typeChoice = getValidatedInt("Enter type choice: ");

    // Common fields
    string id = getValidatedInput("Enter Part ID: ");
    // Check if ID already exists
    if (inventory.findPartById(id)) { // Note: findPartById sorts inventory
         cout << "Error: Part with ID " << id << " already exists." << endl;
         return;
    }
    string name = getValidatedInput("Enter Name: ");
    double price = getValidatedDouble("Enter Price: $");
    int quantity = getValidatedInt("Enter Quantity: ");

    // Hardware/Peripheral common fields
    string mfr_brand;
    int warranty = 0;
    string connType;

    if (typeChoice >= 1 && typeChoice <= 3) { // Hardware
        mfr_brand = getValidatedInput("Enter Manufacturer: ");
        warranty = getValidatedInt("Enter Warranty (months): ");
    } else if (typeChoice >= 4 && typeChoice <= 6) { // Peripheral
        mfr_brand = getValidatedInput("Enter Brand: ");
        connType = getValidatedInput("Enter Connectivity (Wired/Wireless/Both): ");
    }

    ComputerPart* newPart = nullptr;

    try {
        switch (typeChoice) {
            case 1: { // Processor
                double clock = getValidatedDouble("Enter Clock Speed (GHz): ");
                int cores = getValidatedInt("Enter Core Count: ");
                string socket = getValidatedInput("Enter Socket Type: ");
                newPart = new Processor(id, name, price, quantity, mfr_brand, warranty, clock, cores, socket);
                break;
            }
            case 2: { // Graphics Card
                int memSize = getValidatedInt("Enter Memory Size (GB): ");
                double coreClk = getValidatedDouble("Enter Core Clock (MHz): ");
                double memClk = getValidatedDouble("Enter Memory Clock (MHz): ");
                newPart = new GraphicsCard(id, name, price, quantity, mfr_brand, warranty, memSize, coreClk, memClk);
                break;
            }
            case 3: { // Motherboard
                 string chip = getValidatedInput("Enter Chipset: ");
                 string form = getValidatedInput("Enter Form Factor: ");
                 string socket = getValidatedInput("Enter Socket: ");
                 newPart = new Motherboard(id, name, price, quantity, mfr_brand, warranty, chip, form, socket);
                 break;
            }
            case 4: { // Keyboard
                string switchT = getValidatedInput("Enter Switch Type: ");
                bool backlit = getValidatedBool("Is it backlit?");
                bool hotSwap = getValidatedBool("Is it hot-swappable?");
                newPart = new Keyboard(id, name, price, quantity, mfr_brand, connType, switchT, backlit, hotSwap);
                break;
            }
             case 5: { // Mouse
                int poll = getValidatedInt("Enter Polling Rate (Hz): ");
                double weight = getValidatedDouble("Enter Weight (g): ");
                int buttons = getValidatedInt("Enter Number of Buttons: ");
                newPart = new Mouse(id, name, price, quantity, mfr_brand, connType, poll, weight, buttons);
                break;
            }
             case 6: { // Monitor
                double size = getValidatedDouble("Enter Screen Size (inches): ");
                string res = getValidatedInput("Enter Resolution (e.g., 1920x1080): ");
                int refresh = getValidatedInt("Enter Refresh Rate (Hz): ");
                string panel = getValidatedInput("Enter Panel Type (e.g., IPS, VA, TN): ");
                newPart = new Monitor(id, name, price, quantity, mfr_brand, connType, size, res, refresh, panel);
                break;
            }
            default:
                cout << "Invalid type choice." << endl;
                break;
        }

        if (newPart) {
            inventory.addPart(newPart); // Inventory takes ownership
            cout << "Part added successfully." << endl;
        } else {
            // If newPart is null after switch (e.g., invalid type), no memory was allocated
             cout << "Failed to create part." << endl;
        }
    } catch (const exception& e) {
        cerr << "Error adding part: " << e.what() << endl;
        delete newPart; // Clean up if allocation succeeded but something else failed
    }
}

void handleRemovePart(Inventory& inventory) {
    cout << "\n--- Remove Part ---" << endl;
    string id = getValidatedInput("Enter the Part ID to remove: ");
    if (inventory.removePart(id)) {
        cout << "Part removed successfully." << endl;
    } else {
        cout << "Part ID not found." << endl;
    }
}

void handleUpdateStock(Inventory& inventory) {
     cout << "\n--- Update Stock ---" << endl;
    string id = getValidatedInput("Enter the Part ID to update stock for: ");
    ComputerPart* part = inventory.findPartById(id);
    if (part) {
        cout << "Current quantity for " << part->getName() << " (ID: " << id << "): " << part->getQuantity() << endl;
        int change = getValidatedInt("Enter quantity change (positive to add, negative to remove): ");
        try {
            part->updateStock(change);
            cout << "Stock updated. New quantity: " << part->getQuantity() << endl;
        } catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } else {
        cout << "Part ID not found." << endl;
    }
}

void handleSortInventory(Inventory& inventory) {
    cout << "\n--- Sort Inventory ---" << endl;
    cout << "Sort by: (id, name, price, performance): ";
    string sortBy = getValidatedInput("");
    transform(sortBy.begin(), sortBy.end(), sortBy.begin(), ::tolower);

    if (sortBy == "id" || sortBy == "name" || sortBy == "price" || sortBy == "performance") {
        inventory.sortInventory(sortBy);
        cout << "Inventory sorted by " << sortBy << "." << endl;
        inventory.displayInventory(false); // Display summary after sorting
    } else {
        cout << "Invalid sort criteria." << endl;
    }
}

void handleSearchPart(Inventory& inventory, bool byId) {
    cout << "\n--- Search Part ---" << endl;
    string key = getValidatedInput(byId ? "Enter Part ID: " : "Enter Part Name: ");
    ComputerPart* part = byId ? inventory.findPartById(key) : inventory.findPartByName(key);
    if (part) {
        cout << "Part found:" << endl;
        part->displayDetails(true);
    } else {
        cout << "Part not found." << endl;
    }
}

// --- Customer Actions --- 

void handleFindRecommendedBuild(Inventory& inventory) {
    cout << "\n--- Find Recommended Build ---" << endl;
    double budget = getValidatedDouble("Enter your approximate budget ($): ");
    string prefCPU = getValidatedInput("Preferred CPU Manufacturer (e.g., Intel, AMD, or leave blank): ");
    string prefGPU = getValidatedInput("Preferred GPU Manufacturer (e.g., NVIDIA, AMD, or leave blank): ");
    string budgetCat = getBudgetCategory(budget);

    cout << "Calculating recommendations based on budget category: " << budgetCat << "..." << endl;

    vector<pair<double, ComputerPart*>> recommendations;
    const auto& parts = inventory.getParts();

    cout << fixed << setprecision(1);

    // Calculate compatibility for all parts
    for (ComputerPart* part : parts) {
        string preference = ""; // Determine preference based on part type
        const Processor* proc = dynamic_cast<const Processor*>(part);
        const GraphicsCard* gpu = dynamic_cast<const GraphicsCard*>(part);
        // Add other types if preferences apply differently

        if (proc) preference = prefCPU;
        else if (gpu) preference = prefGPU;
        // For others (motherboard, peripherals), manufacturer preference might be less critical or use a general preference

        double score = part->getCompatibilityRate(preference, budgetCat);
        if (score > 0) { // Only recommend parts with some compatibility
             recommendations.push_back({score, part});
        }
    }

    // Sort recommendations by score (highest first)
    sort(recommendations.rbegin(), recommendations.rend(), 
         [](const auto& a, const auto& b) {
             return a.first < b.first; // Sort by score (first element of pair)
         });

    cout << "\n--- Top Recommendations ---" << endl;
    if (recommendations.empty()) {
        cout << "No suitable parts found for your criteria." << endl;
    } else {
        int count = 0;
        for (const auto& rec : recommendations) {
            if (++count > 10) break; // Show top 10 recommendations
            cout << "\nCompatibility Score: " << rec.first << "%" << endl;
            rec.second->displayDetails(false); // Display summary details
        }
    }
}

// --- Main Loop --- 

int main() {
    Inventory inventory("data/inventory.csv"); // Load inventory from data file

    int mainChoice;
    do {
        displayMainMenu();
        mainChoice = getValidatedInt("");

        if (mainChoice == 1) { // Customer Login
            int customerChoice;
            do {
                displayCustomerMenu();
                customerChoice = getValidatedInt("");
                switch (customerChoice) {
                    case 1: handleFindRecommendedBuild(inventory); break;
                    case 2: inventory.displayInventory(false); break; // Summary view
                    case 3: handleSearchPart(inventory, true); break;
                    case 4: handleSearchPart(inventory, false); break;
                    case 0: cout << "Logging out." << endl; break;
                    default: cout << "Invalid choice. Please try again." << endl; break;
                }
            } while (customerChoice != 0);

        } else if (mainChoice == 2) { // Staff Login
            int staffChoice;
            do {
                displayStaffMenu();
                staffChoice = getValidatedInt("");
                switch (staffChoice) {
                    case 1: inventory.displayInventory(false); break;
                    case 2: inventory.displayInventory(true); break;
                    case 3: handleAddPart(inventory); break;
                    case 4: handleRemovePart(inventory); break;
                    case 5: handleUpdateStock(inventory); break;
                    case 6: handleSearchPart(inventory, true); break;
                    case 7: handleSearchPart(inventory, false); break;
                    case 8: handleSortInventory(inventory); break;
                    case 9: inventory.saveInventory(); cout << "Inventory saved to file." << endl; break;
                    case 0: cout << "Logging out." << endl; break;
                    default: cout << "Invalid choice. Please try again." << endl; break;
                }
            } while (staffChoice != 0);
        }
        else if (mainChoice != 0) {
             cout << "Invalid choice. Please try again." << endl;
        }

    } while (mainChoice != 0);

    cout << "Exiting program. Saving inventory..." << endl;
    inventory.saveInventory(); // Save inventory on exit
    cout << "Inventory saved. Goodbye!" << endl;

    return 0;
} 
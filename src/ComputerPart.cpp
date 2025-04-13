#include "ComputerPart.h"

#include <stdexcept> // For std::invalid_argument

using namespace std;

void ComputerPart::updateStock(int changeQuantity) {
    if (quantity + changeQuantity < 0) {
        throw invalid_argument("Stock cannot be negative.");
    }
    quantity += changeQuantity;
} 
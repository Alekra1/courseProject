#include "Processor.h"
#include <iostream>

int main() {
    // Create a sample processor
    Processor cpu("CPU001", "Intel Core i7-12700K", 399.99, 10,
                 "Intel", 36, 3.6, 12, "LGA1700");

    // Display basic information
    std::cout << "Basic Information:" << std::endl;
    std::cout << "-----------------" << std::endl;
    cpu.displayDetails(false);

    std::cout << "\nDetailed Information:" << std::endl;
    std::cout << "---------------------" << std::endl;
    cpu.displayDetails(true);

    // Calculate and display compatibility rate
    std::cout << "\nCompatibility Analysis:" << std::endl;
    std::cout << "----------------------" << std::endl;
    double compatibility = cpu.getCompatibilityRate("Intel", "high");
    std::cout << "Compatibility Rate: " << compatibility << "%" << std::endl;

    return 0;
} 
# Computer Parts Inventory Management System - Design Document

## 1. Abstract Data Types (ADTs)

### 1.1 ComputerPart ADT
```cpp
class ComputerPart {
    // Core attributes
    string partID;
    string name;
    double price;
    int quantity;
    
    // Pure virtual methods
    virtual void displayDetails(bool detailed = false) = 0;
    virtual pair<double, double> computeAdditionalMetrics() = 0;
    virtual double getCompatibilityRate(const string& userPreference, const string& budgetCategory) = 0;
    
    // Concrete methods
    void updateStock(int newQuantity);
};
```

### 1.2 Hardware ADT
```cpp
class Hardware : public ComputerPart {
    // Additional attributes
    string manufacturer;
    int warrantyPeriod;
};
```

### 1.3 Peripheral ADT
```cpp
class Peripheral : public ComputerPart {
    // Additional attributes
    string brand;
    string connectivityType;
};
```

## 2. Class Hierarchy

### 2.1 Base Class
- **ComputerPart** (Abstract)
  - Core attributes and polymorphic methods
  - Defines the interface for all computer parts

### 2.2 Intermediate Classes
- **Hardware** (Abstract)
  - Inherits from ComputerPart
  - Adds manufacturer and warranty information
  - Base for internal components

- **Peripheral** (Abstract)
  - Inherits from ComputerPart
  - Adds brand and connectivity information
  - Base for external devices

### 2.3 Specialized Classes

#### Internal Components
- **Processor**
  - Attributes: clockSpeed, coreCount, socketType
  - Performance metrics based on core count and clock speed

- **GraphicsCard**
  - Attributes: memorySize, coreClock, memoryClock
  - Performance metrics based on memory and clock speeds

- **Motherboard**
  - Attributes: chipset, formFactor, socket
  - Compatibility metrics based on socket and form factor

#### Peripherals
- **Keyboard**
  - Attributes: switchType, backlit, isHotSwappable
  - Performance metrics based on switch type and features

- **Mouse**
  - Attributes: pollingRate, weight, numberOfButtons
  - Performance metrics based on polling rate and features

- **Monitor**
  - Attributes: screenSize, resolution, refreshRate, panelType
  - Performance metrics based on resolution and refresh rate

## 3. Algorithms and Their Evaluation

### 3.1 Search Algorithms

#### Binary Search
- **Purpose**: Locate parts by partID or name
- **Implementation**: 
  - Precondition: Collection must be sorted
  - Time Complexity: O(log n)
  - Space Complexity: O(1)
- **Use Case**: Efficient lookup of specific parts in sorted inventory

### 3.2 Sorting Algorithms

#### Quicksort
- **Purpose**: Sort inventory by various attributes (price, performance metrics)
- **Implementation**:
  - Time Complexity: Average O(n log n), Worst O(n²)
  - Space Complexity: O(log n)
  - Pivot Selection: Median-of-three for better performance
- **Use Cases**:
  - Price-based sorting for budget filtering
  - Performance metric sorting for recommendations
  - Name-based sorting for alphabetical listing

### 3.3 Performance Metrics Algorithms

#### computeAdditionalMetrics()
- **Purpose**: Calculate performance and price-performance ratio
- **Implementation**:
  - Component-specific calculations
  - Time Complexity: O(1) for each component
  - Space Complexity: O(1)
- **Use Cases**:
  - Performance evaluation
  - Price-performance comparison
  - Compatibility calculations

#### getCompatibilityRate()
- **Purpose**: Calculate component compatibility with user preferences
- **Implementation**:
  - Weighted scoring system
  - Time Complexity: O(1) for each component
  - Space Complexity: O(1)
- **Use Cases**:
  - PC build recommendations
  - Component compatibility checking
  - User preference matching

### 3.4 File I/O Operations
- **Purpose**: Load and save inventory data
- **Implementation**:
  - Time Complexity: O(n) where n is number of items
  - Space Complexity: O(n)
- **Use Cases**:
  - Initial inventory loading
  - Inventory updates
  - State persistence

## 4. Data Structure Selection

### 4.1 Main Collection
- **Structure**: `vector<ComputerPart*>`
- **Rationale**:
  - Dynamic sizing for inventory changes
  - Random access for efficient searching
  - Polymorphic behavior support
  - Efficient for sorting operations

### 4.2 Supporting Structures
- **Order Management**: `vector<Order>`
- **User Management**: `map<string, User>`
- **Temporary Storage**: `vector<ComputerPart*>` for sorting and filtering

## 5. Performance Considerations

### 5.1 Memory Management
- Smart pointers for automatic memory management
- Proper virtual destructors in base class
- Efficient string handling with move semantics

### 5.2 Algorithm Optimization
- Binary search for O(log n) lookups
- Quicksort for O(n log n) sorting
- Cached metrics for frequently accessed data

### 5.3 Scalability
- Modular design for easy extension
- Efficient file I/O with buffering
- Optimized data structures for large inventories 
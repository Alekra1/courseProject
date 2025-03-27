**1. Problem Description**  
The goal of the project is to develop a computer parts and peripheral shop inventory management system. The program will load inventory from file, modify/process orders, update stock dynamically, and save the changes back to file. It will manipulate the inventory by sorting (using quicksort based on attributes such as price, name, etc.) and by providing the ability to search for orders or computer parts using a binary search algorithm. Several helper classes will facilitate the creation and editing of orders as well as the updating of stock and inventory. Three polymorphic functions are initially implemented: displayDetails() to display all the details of a particular computer part, computeAdditionalMetrics() to calculate its performance and performance per price ratio, and getCompatibilityRate() will evaluate a compatibility percentage for each component, thereby recommending the best match (for example, the best CPU) for the user's build. At startup, the program will also ask the user to log in either as a customer or as staff. Customers will be guided through the component selection process, while staff members will have access to inventory management functions such as adding, removing, and sorting items.

**2. Three-Level Class Hierarchy**

_Base Class:_

- **ComputerPart (Abstract)**
    
    - _Attributes:_
        
        - partID
            
        - name
            
        - price
            
        - quantity
            
    - _Methods:_
        
        - virtual void displayDetails(bool detailed = false) = 0;
            
        - virtual std::pair<double, double> computeAdditionalMetrics() = 0; (computes performance-core score and price-to-performance ratio)
            
        - virtual double getCompatibilityRate(const std::string& userPreference, const std::string& budgetCategory) = 0;
            
        - void updateStock(int newQuantity);
            

_Intermediate Classes:_

- **Hardware (Abstract, derived from ComputerPart)**
    
    - _Additional Attributes:_
        
        - manufacturer
            
        - warrantyPeriod
            
- **Peripheral (Abstract, derived from ComputerPart)**
    
    - _Additional Attributes:_
        
        - brand
            
        - connectivityType
            

_Specialized Classes:_

- **InternalComponent Derived Classes:**
    
    - **Processor**
        
        - _Additional Attributes:_ clockSpeed, coreCount, socketType
            
    - **GraphicsCard**
        
        - _Additional Attributes:_ memorySize, coreClock, memoryClock
            
    - **Motherboard**
        
        - _Additional Attributes:_ chipset, formFactor, socket
            
- **Peripheral Derived Classes:**
    
    - **Keyboard**
        
        - _Additional Attributes:_ switchType, backlit, isHotSwappable
            
    - **Mouse**
        
        - _Additional Attributes:_ pollingRate, weight, numberOfButtons
            
    - **Monitor**
        
        - _Additional Attributes:_ screenSize, resolution, refreshRate, panelType
            

Each specialized class will override the displayDetails(), computeAdditionalMetrics(), and now also the getCompatibilityRate() functions. The displayDetails() method will present specific attributes along with the computed metrics. The computeAdditionalMetrics() method calculates the performance-core score and the price-to-performance ratio. Finally, the getCompatibilityRate() method will use these metrics along with user preferences (such as manufacturer and budget) to calculate a compatibility percentage for recommending the best-suited component.

**3. Collection of Objects and Functionality**

_Collection Representation:_  
The system will store an inventory as a collection of pointers to ComputerPart objects, using a vector<ComputerPart*>.

_Implemented Functionality:_

- **File I/O Operations:**
    
    - Load initial inventory data from input files.
        
    - Save updated inventory data back to files.
        
- **Search and Sort Algorithms:**
    
    - Implement binary search to locate parts by partID or name.
        
    - Use quicksort to order the inventory based on attributes such as price or computed performance metrics.
        
- **Inventory Update Operations:**
    
    - Update the inventory when parts are sold or restocked.
        
- **Display Operations:**
    
    - Provide detailed output for each part, including both static information and computed additional metrics.
        
- **User Interface and Compatibility Evaluation:**
    
    - At startup, prompt the user to log in either as a customer or as staff.
        
    - For customers, ask configuration questions (budget, preferred GPU manufacturer, preferred CPU manufacturer) to guide the PC build recommendation process.
        
    - The new polymorphic function **getCompatibilityRate()** will compute a compatibility percentage based on performance metrics, price-to-performance ratio, and user-specified preferences.
        
    - For staff, provide options to manipulate the inventory (add, remove, sort, etc.).
        

**4. Polymorphic Functions**

- **displayDetails():**  
    This function displays main attributes of current component (such as partID, name, price and quantity), along with component’s specific details (such as coreCount and clockSpeed for cpu as an example). Also, it displays additional metrics calculated by other polymorphic function – computeAdditionalMetrics() which is described below. To sum up this function will display all the details of the component, basic, niche and additional metrics.
    
- **computeAdditionalMetrics():**
    

This function will have two sub functions – performance and price-per-performance:

- computePeformance() will evaluate the performance using components specific metrics. For example, cpu would have number of cores multiplied by clockSpeed.
    
- computePricePerPerformance() will take the calculated performance by above function, and divide it by price, so the corresponding coefficient will be calculated.
    

This additional metrics will be essential for calculating the compatibility rate, that will be used to create a custom PC builds that will closely match with the needs and preferences of particular user.

- **getCompatibilityRate():**  
    This function takes metrics, calculated by computeAdditionalMetrics(), along with user specific preferences (such as budget category, and preferred manufacturers) to calculate the compatibility rate for each component. This rate represents the matching percentage of it to the particular user.

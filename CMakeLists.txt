cmake_minimum_required(VERSION 3.10)
project(ComputerPartsShop)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
add_executable(computer_parts_shop
    src/main.cpp
    src/Processor.cpp
)

# Add include directory
target_include_directories(computer_parts_shop PRIVATE include) 
cmake_minimum_required(VERSION 3.10)
project(ComputerPartsShop)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatically find all source files in the src directory
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Add executable
add_executable(computer_parts_shop ${SOURCE_FILES})

# Add include directory
target_include_directories(computer_parts_shop PRIVATE include)

# Optional: Add compiler flags (e.g., for warnings)
# target_compile_options(computer_parts_shop PRIVATE -Wall -Wextra -pedantic) 
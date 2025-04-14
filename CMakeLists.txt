cmake_minimum_required(VERSION 3.10)
project(ComputerPartsShop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(computer_parts_shop ${SOURCE_FILES})

target_include_directories(computer_parts_shop PRIVATE include) 
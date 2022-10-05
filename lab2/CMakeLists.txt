cmake_minimum_required(VERSION 3.16)

project(lab2)

add_executable(parent
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/src/parent.cpp
    ${PROJECT_SOURCE_DIR}/include/parent.hpp)
            
target_include_directories(parent PRIVATE include)

add_executable(child
    ${PROJECT_SOURCE_DIR}/src/child.cpp)
        
add_dependencies(parent child)
cmake_minimum_required(VERSION 3.24.1)

project(LabOS CXX)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

include(FindThreads)

add_subdirectory(lab2)

add_subdirectory(lab3)

add_subdirectory(tests)
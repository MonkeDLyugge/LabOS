cmake_minimum_required(VERSION 3.24.1)

project(LabOS)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(lab2)

add_subdirectory(tests)
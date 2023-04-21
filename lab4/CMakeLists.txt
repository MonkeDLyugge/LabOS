set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread -lrt")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(parent1.out
    main.cpp
    src/parent.cpp
    include/parent.hpp)

target_include_directories(parent1.out PRIVATE include)

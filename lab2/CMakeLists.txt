add_executable(parent.out
    main.cpp
    src/parent.cpp
    include/parent.hpp)
            
target_include_directories(parent.out PRIVATE include)

add_executable(child.out
    src/child.cpp)
        
add_dependencies(parent.out child.out)
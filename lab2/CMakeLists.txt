add_executable(parent
    main.cpp
    src/parent.cpp
    include/parent.hpp)
            
target_include_directories(parent PRIVATE include)

add_executable(child
    src/child.cpp)
        
add_dependencies(parent child)
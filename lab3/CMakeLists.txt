add_executable(main
               main.cpp
               src/t_handler.cpp
               include/t_handler.hpp)

target_include_directories(main PRIVATE include)

target_link_libraries(main PRIVATE Threads::Threads)


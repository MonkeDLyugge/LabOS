#include <iostream>
#include <cstdio>
#include <ctime>
    
#include "t_handler.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Wrong arguments number");
        return -1;
    }

    int numberOfExperiments = std::atoi(argv[1]);

    if (numberOfExperiments <= 0) {
        perror("Argument must be more than ZERO");
        return -1;
    }

    int sum = Chances(numberOfExperiments);

    std::cout << (double) sum / (double) numberOfExperiments << "\n"; 

    return 0;
}
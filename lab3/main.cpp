#include <iostream>
#include <cstdio>
#include <ctime>
#include <sstream>
    
#include "t_handler.hpp"

using namespace std;

int to_int(char* string) {
    stringstream ss;
    int result;
    ss << string;
    ss >> result;
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Wrong arguments number");
        return -1;
    }

    int number_of_experiments = to_int(argv[1]);

    if (number_of_experiments <= 0) {
        perror("Argument must be more than ZERO");
        return -1;
    }

    srand(time((time_t*) (number_of_experiments * (int) time(nullptr))));

    NewDeck();

    ThreadExperiment(2, number_of_experiments);

    int sum = 0;
    for (auto i = 0; i < experiment_result.size(); i++) {
        sum += experiment_result[i];
    }

    cout << (double) sum / (double) experiment_result.size() << "\n"; 

    return 0;
}
#include <iostream>
#include <cstdio>
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

    NewDeck();

    ThreadExperiment(2, to_int(argv[1]));

    int sum = 0;
    for (auto i = 0; i < experiment_result.size(); i++) {
        sum += experiment_result[i];
    }

    cout << (double) sum / (double) experiment_result.size(); 

    return 0;
}
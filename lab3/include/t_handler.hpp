#ifndef THANDLER_HPP
#define THANDLER_HPP

#include <string>
#include <vector>

using namespace std;

struct card {
    string name; // = {2, 3, 4, ..., J, Q, K, T};
    char suit; // = {D, H, C, S}
};

extern card deck[52];

extern vector<bool>experiment_result;

void ThreadExperiment(int thread_count, int current_experiment);

void NewDeck();

#endif
#ifndef THANDLER_HPP
#define THANDLER_HPP

#include <string>
#include <vector>
#include <iostream>

struct TCard {
    std::string name; // = {2, 3, 4, ..., J, Q, K, T};
    char suit; // = {D, H, C, S}
};

const int CARDS = 52;
const int CARD_NAMES = 13;

std::vector<TCard> NewDeck();

void* ThreadExperiment(void* argv);

int Chances(int numberOfThreads);

#endif
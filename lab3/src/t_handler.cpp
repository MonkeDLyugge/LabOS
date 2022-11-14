#include <thread>

#include "t_handler.hpp"

using namespace std;

card deck[52];
vector<bool>experiment_result;

void ThreadExperiment(int thread_count, int current_experiment) {
    if (current_experiment == 0) {
        return;
    }

    thread new_thread(ThreadExperiment, thread_count + 1, current_experiment - 1);

    int first_card = rand() % 53;
    int second_card = rand() % 53;
    while (first_card == second_card) {
        second_card = rand() % 53;
    }

    experiment_result.push_back(deck[first_card].name == deck[second_card].name); 
    new_thread.join();
}

void NewDeck() {
    string names[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10",
                        "J", "Q", "K", "T"};
    int k = 0;
    card new_card;
    for (int i = 0; i < 13; i++) {
        new_card.name = names[i];
        new_card.suit = 'D';
        deck[k] = new_card;
        k++;
        new_card.suit = 'C';
        deck[k] = new_card;
        k++;
        new_card.suit = 'H';
        deck[k] = new_card;
        k++;
        new_card.suit = 'S';
        deck[k] = new_card;
        k++;
    }
}
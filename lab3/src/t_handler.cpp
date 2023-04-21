#include "t_handler.hpp"
#include <pthread.h>

struct TData {
    std::vector<TCard>& deck;
    int success;
    int thread;

    TData(std::vector<TCard>& d, int s, int t) : deck(d), success(s), thread(t) {} 
};

std::vector<TCard> NewDeck() {
    const std::string names[CARD_NAMES] = {"2", "3", "4", "5", "6", "7", "8", "9", "10",
                        "J", "Q", "K", "T"};
    int k = 0;
    TCard newCard;
    std::vector<TCard> deck(CARDS);
    for (int i = 0; i < CARD_NAMES; i++) {
        newCard.name = names[i];
        newCard.suit = 'D';
        deck[k] = newCard;
        k++;
        newCard.suit = 'C';
        deck[k] = newCard;
        k++;
        newCard.suit = 'H';
        deck[k] = newCard;
        k++;
        newCard.suit = 'S';
        deck[k] = newCard;
        k++;
    }
    return deck;
}

void* ThreadExperiment(void* argv) {
    std::vector<TCard>deck = ((TData *) argv)->deck;
    int &thread = ((TData *) argv)->thread;
    int &success = ((TData *) argv)->success;
    
    srand(time(nullptr) * thread);

    int firstCard = rand() % CARDS;
    srand(time(nullptr) * thread * 2);
    int secondCard = rand() % CARDS;
    while (firstCard == secondCard) {
        secondCard = rand() % CARDS;
    }

    success += (deck[firstCard].name == deck[secondCard].name);

    return nullptr;
}

int Chances(int numberOfThreads) {

    std::vector<pthread_t>threads(numberOfThreads);
    
    std::vector<TCard> deck = NewDeck();

    TData data(deck, 0, numberOfThreads);

    for (int i = 0; i < numberOfThreads; i++) {
        if (pthread_create(&threads[i], nullptr, ThreadExperiment, &data)) {
            perror("Thread create error");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < numberOfThreads; i++) {
        if (pthread_join(threads[i], nullptr) != 0) {
            perror("Can't wait for thread\n");
            exit(EXIT_FAILURE);
        }
    }
    
    return data.success;
}
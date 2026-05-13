#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include "Player.hpp"

const int MAX_PLAYERS = 100000;

class Matchmaking
{

private:
    Player players[MAX_PLAYERS];
    int size;

public:
    Matchmaking();
    ~Matchmaking();

    bool insert(Player player);
    bool removePlayer(int id);

    void sortByScoreInsertion();
    bool comesBefore(const Player& a, const Player& b);
    void merge(int mid, int left, int right);
    void mergeSort(int left, int right);
    void sortByScoreMerge();

    Player *formGroup(int groupSize, int delta, int *n);

    Player *getWaitingPlayers(int *n);

    void printWaitingPlayers();
};

#endif
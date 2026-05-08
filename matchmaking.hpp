#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include "player.hpp"

const int MAX_PLAYERS = 100000;

class Matchmaking
{

private:
    Player players[MAX_PLAYERS];
    int size;

    void merge(int left, int mid, int right);
    void mergeSort(int left, int right);

public:
    Matchmaking();
    ~Matchmaking();

    bool insert(Player player);
    bool removePlayer(int id);

    void sortByScoreInsertion();
    void sortByScoreMerge();

    Player *formGroup(int groupSize, int delta, int *n);

    Player *getWaitingPlayers(int *n);

    void printWaitingPlayers();
};

#endif
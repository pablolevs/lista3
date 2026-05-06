#include "Matchmaking.hpp"

Matchmaking::Matchmaking() {
    size = 0;
}

Matchmaking::~Matchmaking() {}

bool Matchmaking::insert(Player player) {
    if (size >= MAX_PLAYERS) {
        return false;
    }

    players[size] = player;

    size++;

    return true;
}

bool Matchmaking::removePlayer(int id) {
    for (int i = 0; i < size; i++) {
        if (players[i].getId() == id) {
            for (int j = i; j < size - 1; j++) {
                players[j] = players[j + 1];
            }

            size--; 

            return true;
        }
    }
    
    return false; 
}
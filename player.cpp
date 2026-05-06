#include "Player.hpp"

Player::Player()
    : id(0), name(""), score(0), timestamp(0) {}

Player::Player(int id, std::string name, int score, int timestamp)
    : id(id), name(name), score(score), timestamp(timestamp) {}

Player::~Player() {}

int Player::getId() {
    return id;
}

std::string Player::getName() {
    return name;
}

int Player::getScore() {
    return score;
}

int Player::getTimestamp() {
    return timestamp;
}


#include "Player.hpp"

Player::Player()
{
    this->id = 0;
    this->name = "";
    this->score = 0;
    this->timestamp = 0;
}

Player::Player(int id, std::string name, int score, int timestamp)
{
    this->id = id;
    this->name = name;
    this->score = score;
    this->timestamp = timestamp;
}

Player::~Player() {}

int Player::getId() const
{
    return this->id;
}

std::string Player::getName() const
{
    return this->name;
}

int Player::getScore() const
{
    return this->score;
}

int Player::getTimestamp() const
{
    return this->timestamp;
}
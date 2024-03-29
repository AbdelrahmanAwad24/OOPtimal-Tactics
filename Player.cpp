#include "Player.hpp"

#include <iostream>

Player::Player(char id) : id_(id), chips_(0), has_passed_(false) {}

Player::~Player() {}

void Player::setId(char id)
{
    id_ = id;
}

char Player::getId()
{
    return id_;
}

void Player::setChips(int chips)
{
    chips_ = chips;
}

int Player::getChips()
{
    return chips_;
}

void Player::setPassed(bool has_passed)
{
    has_passed_ = has_passed;
}

bool Player::hasPassed()
{
    return has_passed_;
}

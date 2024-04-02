#include "Player.hpp"

#include <iostream>

Player::Player(char id) : id_(id), chips_(0), has_passed_(false), claimed_fields_(0) {}

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

void Player::calcClaimedFields()
{
    // claimed_fields_ = claimed_fields_ + claimed_fields;
    claimed_fields_++;
}

void Player::setClaimedFields(int claimed_fields)
{
    claimed_fields_ = claimed_fields;
}

int Player::getClaimedFields()
{
    return claimed_fields_;
}

void Player::setPassed(bool has_passed)
{
    has_passed_ = has_passed;
}

bool Player::hasPassed()
{
    return has_passed_;
}

#include "Field.hpp"

#include <iostream>

Field::Field(Player *player, int chips, bool is_water) : player_(player), chips_(chips), is_water_(is_water) {}

Field::~Field() {}

void Field::setPlayer(Player *player)
{
    player_ = player;
}

Player *Field::getPlayer()
{
    return player_;
}

void Field::setChips(int chips)
{
    chips_ = chips;
}

int Field::getChips()
{
    return chips_;
}

bool Field::isWater()
{
    return is_water_;
}

void Field::setIsWater(bool isWater)
{
    is_water_ = isWater;
}

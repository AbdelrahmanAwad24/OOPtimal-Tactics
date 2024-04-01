#include "Field.hpp"

#include <iostream>

Field::Field(Player *player, int chips, bool is_water) : player_(player), chips_(chips), is_water_(is_water)
{
    // if (is_water_)
    // {
    //     std::cout << " ~ ";
    // }
    // else if (player)
    // {
    //     std::cout
    //         << player->getId() << " " << chips_;
    // }
    // else
    // {
    //     std::cout << "   ";
    // }
}

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
    chips_ = chips_ + chips;
}

void Field::removeChips(int chips)
{
    chips_ = chips_ - chips;
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

// int Field::counter = 0;

void Field::printField()
{
    if (isWater())
    {
        std::cout << " ~ ";
    }
    else if (getPlayer())
    {
        std::cout
            << getPlayer()->getId() << " " << chips_;
        // counter++;
    }
    else
    {
        std::cout << "   ";
    }
}
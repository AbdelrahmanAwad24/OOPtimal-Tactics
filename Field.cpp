#include "Field.hpp"

#include <iostream>

Field::Field(Player *player, int chips, bool is_water, bool is_empty) : player_(player), chips_(chips), is_water_(is_water), is_empty_(is_empty)
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

void Field::setIsWater(bool is_water)
{
    is_water_ = is_water;
}

bool Field::isEmpty()
{
    return is_empty_;
}

void Field::setIsEmpty(bool is_empty)
{
    is_empty_ = is_empty;
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
    else if (isEmpty())
    {
        // setIsEmpty(true);
        std::cout << "   ";
    }
}
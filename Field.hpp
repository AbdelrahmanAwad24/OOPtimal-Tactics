#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>
#include <string>
#include "Player.hpp"

class Field
{
private:
    Player *player_;
    int chips_;
    bool is_water_;
    // static int counter;

public:
    Field(Player *player, int chips, bool is_water);
    ~Field();

    Player *getPlayer();
    void setPlayer(Player *player);
    int getChips();
    void setChips(int chips);
    bool isWater();
    void setIsWater(bool isWater);
    void printField();
    void removeChips(int chips);
};

#endif
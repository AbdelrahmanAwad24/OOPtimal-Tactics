#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>

class Player
{
private:
    char id_;
    int chips_;
    bool has_passed_;
    int claimed_fields_;

public:
    Player(char id);
    Player(const Player &other) = delete;

    ~Player();

    void setId(char id);
    char getId();
    void setChips(int chips);
    int getChips();
    void calcClaimedFields();
    void setClaimedFields(int claimed_fields);
    int getClaimedFields();
    void setPassed(bool has_passed);
    bool hasPassed();
};

#endif
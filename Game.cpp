#include "Game.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#define CONFIG_MAGIC_NUMBER "OOP"

Game::Game(int maximum_rounds, char *config_path)
    : map_(nullptr), player_a_(nullptr), player_b_(nullptr),
      current_round_(1), max_rounds_(maximum_rounds), phase_(Phase::PLACEMENT),
      active_player_(nullptr)
{
    Player *player_a = new Player('A');
    setPlayerA(player_a);
    Player *player_b = new Player('B');
    setPlayerB(player_b);
    setActivePlayer(player_a);
    map_ = new Map(config_path, player_a_, player_b_);
    // setMap(map_);
}

Game::~Game()
{
    delete map_;
    delete player_a_;
    delete player_b_;
}

bool Game::isValidRoundNumber(int rounds)
{
    return rounds >= 1;
}

int Game::getRoundNumber(char *string)
{
    std::string roundStr(string); // Convert the char* to std::string
    int roundNumber;
    bool conversionSuccess = Utils::decimalStringToInt(roundStr, roundNumber);
    if (conversionSuccess && isValidRoundNumber(roundNumber))
    {
        return roundNumber;
    }
    else
    {
        return -1; // Return -1 if conversion fails or the round number is invalid
    }
}

bool Game::isValidConfig(char *config_path)
{
    std::ifstream file(config_path);
    std::string magic_number;
    std::getline(file, magic_number);
    return file.is_open() && magic_number == CONFIG_MAGIC_NUMBER;
}

int Game::toggle = 1;
void Game::placmentPhase()
{
    std::cout << "\n------------------\nPlacement Phase\n------------------" << std::endl;
    if (toggle)
    {
        map_->printMap();
    }

    std::cout << "Player " << getActivePlayer()->getId() << ", you have " << getActivePlayer()->getChips() << " chip(s) left, where and how do you want to place your chips ? " << std::endl;
}

void Game::movementPhase()
{
    std::cout << "\n------------------\nMovement Phase\n------------------" << std::endl;
    if (toggle)
    {
        map_->printMap();
    }
    std::cout << "Player " << getActivePlayer()->getId() << ", what do you want to do ? " << std::endl;
}

void Game::start()
{
    std::cout << "Welcome to OOPtimal Tactics!\nPlaying maximum of " << max_rounds_ << " round(s)!" << std::endl;
    std::cout << "\n------------------\nRound 1/" << max_rounds_ << " starts!\n------------------" << std::endl;
    double gained_chips = std::ceil(map_->getCounter() / 3.0);
    player_a_->setChips(gained_chips);
    player_b_->setChips(gained_chips);
    // std::cout << "\n------------------\nPlacement Phase\n------------------" << std::endl;
    // map_->printMap();
}

void Game::execute(Command command)
{

    switch (command.getType())
    {
    case CommandType::PLACE:
        std::cout << map_->getColumns() << std::endl;
        break;

    case CommandType::PASS:
        std::cout << "Pass command!" << std::endl;
        break;

    case CommandType::MOVE:
        // Implement logic to handle moving chips on the map
        std::cout << "Move command!" << std::endl;

        break;

    case CommandType::MAP:
        toggle = 0;
        std::cout << "Map command!" << std::endl;

        break;

    case CommandType::INFO:
        // Implement logic to display game information
        std::cout << "Info command!" << std::endl;

        break;

    case CommandType::QUIT:
        // Implement logic to end the game
        std::cout << "Quit command!" << std::endl;

        break;

    case CommandType::INVALID:
        // Handle invalid command type
        std::cout << "Invalid command!" << std::endl;
        break;

    case CommandType::WRONG_PARAM:
        // Handle command with wrong parameters
        std::cout << "Command with wrong parameters!" << std::endl;
        break;
    }
    if (phase_ == Phase::PLACEMENT)
    {
        setActivePlayer(player_b_);
    }
    if (phase_ == Phase::MOVEMENT)
    {
        if (active_player_ == player_a_)
        {
            setActivePlayer(player_b_);
        }
        else
        {
            setActivePlayer(player_a_);
        }
    }
}

int Game::toggle_flag = 0;
bool Game::isRunning()
{
    // if (toggle_flag)
    // {
    //     placmentPhase();
    //     // toggle_flag = !toggle_flag;
    //     toggle = !toggle;
    // }
    // else if (!toggle_flag)
    // {
    //     placmentPhaseRev();
    //     toggle_flag = !toggle_flag;
    // }

    placmentPhase();
    return phase_ != Phase::END;
}

void Game::setMap(Map *map)
{
    map_ = map;
}

Map *Game::getMap()
{
    return map_;
}

void Game::setPlayerA(Player *player)
{
    player_a_ = player;
}

Player *Game::getPlayerA()
{
    return player_a_;
}

void Game::setPlayerB(Player *player)
{
    player_b_ = player;
}

Player *Game::getPlayerB()
{
    return player_b_;
}

void Game::setCurrentRound(int round)
{
    current_round_ = round;
}

int Game::getCurrentRound()
{
    return current_round_;
}

void Game::setMaxRounds(int max_rounds)
{
    max_rounds_ = max_rounds;
}

int Game::getMaxRounds()
{
    return max_rounds_;
}

void Game::setPhase(Phase phase)
{
    phase_ = phase;
}

Phase Game::getPhase()
{
    return phase_;
}

void Game::setActivePlayer(Player *player)
{
    active_player_ = player;
}

Player *Game::getActivePlayer()
{
    return active_player_;
}

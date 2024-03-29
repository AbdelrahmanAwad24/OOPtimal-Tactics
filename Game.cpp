#include "Game.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <string>

#define CONFIG_MAGIC_NUMBER "OOP\n"

Game::Game(int maximum_rounds, char *config_path)
    : map_(nullptr), player_a_(nullptr), player_b_(nullptr),
      current_round_(0), max_rounds_(maximum_rounds), phase_(Phase::PLACEMENT),
      active_player_(nullptr)
{
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

void Game::start()
{
    // Implementation to start the game
    std::cout << "Welcome to OOPtimal Tactics!\nPlaying maximum of <ROUNDS> round(s) !" << std::endl;
}

void Game::execute(Command command)
{
    // Implementation to execute a command
    std::cout << "hello" << std::endl;
}

bool Game::isRunning()
{
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

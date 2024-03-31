#include "Game.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <string>

#define CONFIG_MAGIC_NUMBER "OOP"

Game::Game(int maximum_rounds, char *config_path)
    : map_(nullptr), player_a_(nullptr), player_b_(nullptr),
      current_round_(1), max_rounds_(maximum_rounds), phase_(Phase::PLACEMENT),
      active_player_(player_a_)
{
    Player *player_a = new Player('A');
    setPlayerA(player_a);
    Player *player_b = new Player('B');
    setPlayerB(player_b);

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

void Game::start()
{
    std::cout << "Welcome to OOPtimal Tactics!\nPlaying maximum of " << max_rounds_ << "round(s) !" << std::endl;
    std::cout << "\n------------------\nRound 1/" << max_rounds_ << " starts!\n------------------\n";
    std::cout << "\n------------------\nPlacement Phase\n------------------\n"
              << std::endl;
    map_->printMap();
}

void Game::execute(Command command)
{
    switch (command.getType())
    {
    case CommandType::PLACE:
        // Implement logic to handle placing chips on the map
        std::cout << map_->getColumns() << std::endl;

        break;

    case CommandType::PASS:
        // Implement logic to handle passing the turn
        std::cout << "Pass command!" << std::endl;

        break;

    case CommandType::MOVE:
        // Implement logic to handle moving chips on the map
        std::cout << "Move command!" << std::endl;

        break;

    case CommandType::MAP:
        // Implement logic to display the current state of the map
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

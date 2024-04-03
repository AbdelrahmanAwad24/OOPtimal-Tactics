#include "Game.hpp"
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#define CONFIG_MAGIC_NUMBER "OOP"
int Game::toggle = 1;
int Game::placement_counter = 0;
int Game::movement_counter = 0;
int Game::toggle_flag = 0;
int Game::placement_header = 1;
int Game::movement_header = 1;

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
}

Game::~Game()
{
    delete map_;
    delete player_a_;
    delete player_b_;
}
void Game::toggleActivePlayer()
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

void Game::handleActivePlayer()
{
    if (phase_ == Phase::PLACEMENT)
    {
        if (current_round_ % 2 == 1)
        { // If round number is odd
            setActivePlayer(player_a_);
        }
        else
        { // If round number is even
            setActivePlayer(player_b_);
        }
    }
    if (phase_ == Phase::MOVEMENT)
    {
        if (current_round_ % 2 == 1)
        { // If round number is odd
            setActivePlayer(player_b_);
        }
        else
        { // If round number is even
            setActivePlayer(player_a_);
        }
    }
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
    std::cout << "Welcome to OOPtimal Tactics!\nPlaying maximum of " << max_rounds_ << " round(s)!" << std::endl;
}

void Game::handlePlace(Command command)
{
    if (phase_ == Phase::PLACEMENT)
    {
        if (command.getParameters().size() == 3)
        {
            int chips = std::stoi(command.getParameters()[0]);
            int column = std::stoi(command.getParameters()[1]);
            int row = std::stoi(command.getParameters()[2]);
            // Check if the provided column and row are within bounds of the map
            if (column >= 1 && column <= map_->getColumns() && row >= 1 && row <= map_->getRows())
            {
                // Place chips at the specified column and row for the active player
                int valid_move = map_->placeChips(column - 1, row - 1, chips, active_player_);
                if (valid_move == 1)
                {
                    active_player_->setChips(active_player_->getChips() - chips);
                }
                else
                {
                    std::cout << "Invalid column or row number!" << std::endl;
                }

                // map_->placeChips(column - 1, row - 1, chips, active_player_);
                if (active_player_->getChips() == 0)
                {
                    active_player_->setPassed(true);
                    toggleActivePlayer();
                    placement_counter++;
                }
                // std::cout << active_player_->getChips() << std::endl;
                if (placement_counter == 2)
                {
                    setPhase(Phase::MOVEMENT);
                    placement_counter = 0;
                }
            }
            else
            {
                std::cout << "[ERROR] Invalid origin!" << std::endl;
            }
        }
        else
        {
            std::cout << "Wrong number of parameters for PLACE command!" << std::endl;
        }
    }
    else
    {
        std::cout << "PLACE command can only be executed during the PLACEMENT phase!" << std::endl;
    }
}

void Game::handleMove(Command command)
{
    if (phase_ == Phase::MOVEMENT)
    {
        if (command.getParameters().size() == 5)
        {
            int chips = std::stoi(command.getParameters()[0]);
            int column = std::stoi(command.getParameters()[1]);
            int row = std::stoi(command.getParameters()[2]);
            int new_column = std::stoi(command.getParameters()[3]);
            int new_row = std::stoi(command.getParameters()[4]);
            // Check if the provided column and row are within bounds of the map
            if (!map_->checkValidField(active_player_, column, row))
            {
                std::cout << "[ERROR] Invalid origin!" << std::endl;
            }
            else
            {
                int valid_move = map_->placeChips(new_column - 1, new_row - 1, chips, active_player_);
                if (valid_move == 1)
                {
                    // Place chips at the specified column and row for the active player
                    map_->moveChips(column - 1, row - 1, chips);
                    // active_player_->setPassed(true);
                    // map_->placeChips(new_column - 1, new_row - 1, chips, active_player_);
                    toggleActivePlayer();
                    if (getActivePlayer()->hasPassed())
                    {
                        toggleActivePlayer();
                    }
                }
                else if (valid_move == 2)
                {
                    map_->moveChips(column - 1, row - 1, chips);
                }
                else
                {
                    std::cout << "[ERROR] Invalid origin!" << std::endl;
                }
            }
        }
    }
    else
    {
        std::cout << "MOVE command can only be executed during the PLACEMENT phase!" << std::endl;
    }
}

void Game::handlePass()
{
    if (active_player_ == player_a_)
    {
        player_a_->setPassed(true);
    }
    else
    {
        player_b_->setPassed(true);
    }
    if (player_a_->hasPassed() && player_b_->hasPassed())
    {
        if (current_round_ == max_rounds_ && phase_ == Phase::MOVEMENT)
        {
            setPhase(Phase::END);
        }
        else
        {
            if (phase_ == Phase::PLACEMENT)
            {
                setPhase(Phase::MOVEMENT);
                placement_header = 1;
                movement_header = 1;
                player_a_->setPassed(false);
                player_b_->setPassed(false);
            }
            else if (phase_ == Phase::MOVEMENT)
            {
                setPhase(Phase::PLACEMENT);
                placement_header = 1;
                movement_header = 1;
                player_a_->setPassed(false);
                player_b_->setPassed(false);
                current_round_++;
            }
        }
    }
}

void Game::execute(Command command)
{

    switch (command.getType())
    {
    case CommandType::PLACE:
        handlePlace(command);
        if (toggle)
        {
            map_->printMap();
        }
        break;

    case CommandType::PASS:
        handlePass();
        toggleActivePlayer();
        break;

    case CommandType::MOVE:
        handleMove(command);
        if (toggle)
        {
            map_->printMap();
        }
        break;

    case CommandType::MAP:
        toggle = !toggle;
        break;

    case CommandType::INFO:
    case CommandType::INVALID:
    case CommandType::QUIT:
    case CommandType::WRONG_PARAM:

        break;
    }
}

void Game::placmentPhase()
{
    std::cout << "Player " << getActivePlayer()->getId() << ", you have " << getActivePlayer()->getChips() << " chip(s) left, where and how do you want to place your chips?" << std::endl;
}

void Game::movementPhase()
{
    std::cout << "Player " << getActivePlayer()->getId() << ", what do you want to do?" << std::endl;
}

void Game::endGame()
{
    player_a_->setClaimedFields(0);
    player_b_->setClaimedFields(0);
    map_->calculateOcuppiedFields();
    std::cout << "------------------\nGAME END!\n\nPlayer A claimed " << player_a_->getClaimedFields() << " field(s)!" << std::endl;
    std::cout << "Player B claimed " << player_b_->getClaimedFields() << " field(s)!" << std::endl;
    if (player_a_->getClaimedFields() != player_b_->getClaimedFields())
    {
        if (player_a_->getClaimedFields() > player_b_->getClaimedFields())
        {
            std::cout << " \nCongratulations, Player A !You won !" << std::endl;
        }
        else
        {
            std::cout << " \nCongratulations, Player B !You won !" << std::endl;
        }
    }
}

bool Game::isRunning()
{
    if (phase_ == Phase::PLACEMENT)
    {
        if (placement_header)
        {
            player_a_->setClaimedFields(0);
            player_b_->setClaimedFields(0);
            map_->calculateOcuppiedFields();
            player_a_->setPassed(false);
            player_b_->setPassed(false);
            double gained_chips_a = std::ceil(player_a_->getClaimedFields() / 3.0);
            double gained_chips_b = std::ceil(player_b_->getClaimedFields() / 3.0);
            player_a_->setChips(gained_chips_a);
            player_b_->setChips(gained_chips_b);
            handleActivePlayer();
            std::cout << "\n------------------\nRound " << current_round_ << "/" << max_rounds_ << " starts!\n------------------" << std::endl;
            std::cout << "\n------------------\nPlacement Phase\n------------------" << std::endl;
            placement_header = 0;
            if (toggle)
            {
                map_->printMap();
            }
        }
        placmentPhase();
    }
    else if (phase_ == Phase::MOVEMENT)
    {
        if (movement_header)
        {
            player_a_->setPassed(false);
            player_b_->setPassed(false);
            handleActivePlayer();
            std::cout << "------------------\nMovement Phase\n------------------" << std::endl;
            movement_header = 0;
            if (toggle)
            {
                map_->printMap();
            }
        }
        movementPhase();
    }
    else
    {
        endGame();
    }
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

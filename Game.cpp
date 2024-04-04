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
// int Game::saved_chips_a = 0;
// int Game::saved_chips_b = 0;

bool Game::isInteger(double number)
{
    return number > 0 && std::floor(number) == number;
}

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

    if (phase_ != Phase::PLACEMENT)
    {
        std::cout << "[ERROR] Entered command is not valid in this phase!" << std::endl;
        return;
    }
    double chips = std::stod(command.getParameters()[0]);
    double column = std::stod(command.getParameters()[1]);
    double row = std::stod(command.getParameters()[2]);
    // check if all inputs is int or not.
    if (!isInteger(chips) || !isInteger(column) || !isInteger(row))
    {
        std::cout << "[ERROR] Invalid amount! Must be a number > 0!" << std::endl;
        return;
    }
    int valid_move = map_->placeChips(column - 1, row - 1, chips, active_player_);
    if (valid_move == 1)
    {
        active_player_->setChips(active_player_->getChips() - chips);
        active_player_->setSavedChips(active_player_->getChips());
    }
    // Check if the provided column and row are within bounds of the map
    if (column <= map_->getColumns() && row <= map_->getRows() && valid_move)
    {
        if (active_player_->getChips() == 0)
        {
            active_player_->setPassed(true);
            toggleActivePlayer();
            placement_counter++;
        }
        if (player_a_->hasPassed() && player_b_->hasPassed())
        {
            setPhase(Phase::MOVEMENT);
        }
    }
    else
    {
        std::cout << "[ERROR] Invalid origin!" << std::endl;
    }
}

void Game::handleMove(Command command)
{
    if (phase_ == Phase::MOVEMENT)
    {
        std::cout << "[ERROR] Entered command is not valid in this phase!" << std::endl;
    }
    double chips = std::stod(command.getParameters()[0]);
    double column = std::stod(command.getParameters()[1]);
    double row = std::stod(command.getParameters()[2]);
    double new_column = std::stod(command.getParameters()[3]);
    double new_row = std::stod(command.getParameters()[4]);
    if (!isInteger(chips) || !isInteger(column) || !isInteger(row) || !isInteger(new_column) || !isInteger(new_row))
    {
        std::cout << "[ERROR] Invalid amount! Must be a number > 0!" << std::endl;
        return;
    }

    // Check if the provided column and row are within bounds of the map
    int check = map_->checkValidField(active_player_, column - 1, row - 1);
    if (!check)
    {
        std::cout << "[ERROR] Invalid origin!" << std::endl;
    }
    else
    {
        int valid_move = map_->placeChips(new_column - 1, new_row - 1, chips, active_player_);
        if (valid_move)
        {
            // Place chips at the specified column and row for the active player
            map_->moveChips(column - 1, row - 1, chips);
            toggleActivePlayer();
            if (getActivePlayer()->hasPassed())
            {
                toggleActivePlayer();
            }
        }
        if (toggle)
        {
            map_->printMap();
        }
    }

    // else
    // {
    //     std::cout << "[ERROR] Entered command is not valid in this phase!" << std::endl;
    // }
}

void Game::handleInfo()
{
    std::cout << "Player " << active_player_->getId() << ":" << std::endl;
    std::cout << "You have " << active_player_->getSavedChips() << " chip(s) saved!" << std::endl;
    std::cout << "You own " << active_player_->getClaimedFields() << " field(s)!\n"
              << std::endl;
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
                active_player_->setSavedChips(active_player_->getChips());
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
        break;

    case CommandType::MAP:
        toggle = !toggle;
        if (toggle)
        {
            map_->printMap();
        }
        break;

    case CommandType::INFO:
        handleInfo();
        break;

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
    player_a_->setClaimedFields(0);
    player_b_->setClaimedFields(0);
    map_->calculateOcuppiedFields();
    int end_flag = 0;
    if (player_a_->getClaimedFields() == 0 || player_b_->getClaimedFields() == 0)
    {
        end_flag = 1;
        endGame();
        setPhase(Phase::END);
    }
    if (!end_flag)
    {
        std::cout << "Player " << getActivePlayer()->getId() << ", what do you want to do?" << std::endl;
    }
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
            std::cout << "\nCongratulations, Player A! You won!" << std::endl;
        }
        else
        {
            std::cout << "\nCongratulations, Player B! You won!" << std::endl;
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
            double gained_chips_a = std::ceil(player_a_->getClaimedFields() / 3.0) + player_a_->getSavedChips();
            double gained_chips_b = std::ceil(player_b_->getClaimedFields() / 3.0) + player_b_->getSavedChips();
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
            player_a_->setClaimedFields(0);
            player_b_->setClaimedFields(0);
            map_->calculateOcuppiedFields();
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

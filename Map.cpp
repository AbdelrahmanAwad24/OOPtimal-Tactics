#include "Map.hpp"
#include "Utils.hpp"
#include <fstream>
#include <iostream>

Map::Map(char *config_path, Player *player_a, Player *player_b)
    : columns_(0), rows_(0), output_active_(false), counter_(0)
{
    std::ifstream configFile(config_path);
    if (!configFile.is_open())
    {
        std::cout << "Error: Unable to open config file." << std::endl;
    }
    std::string line;
    std::getline(configFile, line);
    std::getline(configFile, line);

    columns_ = line.at(0) - '0'; // convert char int to tint
    rows_ = line.at(2) - '0';

    fields_.resize(rows_);
    for (auto &row : fields_)
    {
        row.resize(columns_);
    }

    for (int i = 0; i < rows_; ++i)
    {
        // std::cout << i + 1 << " ";
        std::getline(configFile, line);
        for (int j = 0; j < columns_; ++j)
        {
            Player *player = nullptr;
            int chips = 0;
            bool is_water = false;
            bool is_empty = false;
            char symbol = line[j];
            if (symbol == 'a')
            {
                player = player_a;
                chips = 1;
                counter_++;
            }
            else if (symbol == 'b')
            {
                player = player_b;
                chips = 1;
            }
            else if (symbol == '-')
            {
                is_water = true;
            }
            else if (symbol == '0')
            {
                is_empty = true;
            }

            fields_[i][j] = new Field(player, chips, is_water, is_empty);
        }
    }
}

Map::~Map()
{
    // Delete dynamically allocated Field objects
    for (auto &row : fields_)
    {
        for (auto &field : row)
        {
            delete field;
        }
    }
}

void Map::printMap()
{
    std::cout << "  |";
    for (int i = 1; i < columns_; i++)
    {
        std::cout << " " << i << " |";
    }
    std::cout << " " << columns_ << " " << std::endl;
    for (int i = 0; i < rows_; ++i)
    {
        std::cout << i + 1 << " ";
        for (int j = 0; j < columns_; ++j)
        {
            std::cout << "|";
            std::string symbol;
            fields_[i][j]->printField();
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Map::calculateOcuppiedFields()
{
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < columns_; ++j)
        {
            if (fields_[i][j]->isEmpty() || fields_[i][j]->isWater())
            {
                continue;
            }
            else
            {
                fields_[i][j]->getPlayer()->calcClaimedFields();
            }
        }
    }
}

void Map::setColumns(int columns)
{
    columns_ = columns;
}

int Map::placeChips(int column, int row, int chips, Player *player)
{
    if (column >= 0 && column < columns_ && row >= 0 && row < rows_)
    {
        // Update the number of chips in the specified field for the given player
        if (fields_[row][column]->isEmpty())
        {
            fields_[row][column]->setPlayer(player);
            fields_[row][column]->setChips(chips);
            return 1;
        }
        if (fields_[row][column]->getPlayer()->getId() == player->getId())
        {
            fields_[row][column]->setPlayer(player);
            fields_[row][column]->setChips(chips);
            return 1;
        }
    }
    return 0;
}

void Map::moveChips(int column, int row, int chips)
{
    if (column >= 0 && column < columns_ && row >= 0 && row < rows_)
    {
        // Update the number of chips in the specified field for the given player
        fields_[row][column]->removeChips(chips);
    }
    else
    {
        std::cout << "Invalid column or row number!" << std::endl;
    }
}

int Map::getColumns()
{
    return columns_;
}

void Map::setCounter(int counter)
{
    counter_ = counter;
}

int Map::getCounter()
{
    return counter_;
}

void Map::setRows(int rows)
{
    rows_ = rows;
}

int Map::getRows()
{
    return rows_;
}

void Map::setFields(const std::vector<std::vector<Field *>> &fields)
{

    fields_ = fields;
}

std::vector<std::vector<Field *>> &Map::getFields()
{
    return fields_;
}

void Map::setOutputActive(bool output_active)
{
    output_active_ = output_active;
}

bool Map::isOutputActive()
{
    return output_active_;
}
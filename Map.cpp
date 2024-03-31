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

    // std::cout << "  |"; //!
    // for (int i = 1; i < columns_; i++)
    // {
    //     std::cout << " " << i << " |";
    // }
    // std::cout << " " << columns_ << " " << std::endl;//!

    for (int i = 0; i < rows_; ++i)
    {
        // std::cout << i + 1 << " ";
        std::getline(configFile, line);
        for (int j = 0; j < columns_; ++j)
        {
            // std::cout << "|";
            Player *player = nullptr;
            int chips = 0;
            bool is_water = false;
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
            fields_[i][j] = new Field(player, chips, is_water);
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
void Map::setColumns(int columns)
{
    columns_ = columns;
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
#include "Map.hpp"
#include "Utils.hpp"
#include <fstream>
#include <iostream>

Map::Map(char *config_path, Player *player_a, Player *player_b)
    : columns_(0), rows_(0), output_active_(false)
{
    std::ifstream configFile(config_path);
    if (!configFile.is_open())
    {
        std::cout << "Error: Unable to open config file." << std::endl;
    }

    std::vector<std::vector<char>> row;
    std::string line;
    std::getline(configFile, line);
    std::getline(configFile, line);

    columns_ = line.at(0) - '0'; // convert char int to tint
    rows_ = line.at(2) - '0';

    while (std::getline(configFile, line))
    {
        std::vector<char> column;
        for (auto c : line)
        {
            column.push_back(c);
        }
        row.push_back(column);
    }
    std::cout << "  |";

    for (int i = 1; i < columns_; i++)
    {
        std::cout << " " << i << " |";
    }
    std::cout << " " << columns_ << " " << std::endl;

    for (size_t i = 0; i < row.size(); ++i)
    {
        std::vector<char> &column = row.at(i);
        std::cout << i + 1 << " |";
        for (size_t j = 0; j < column.size() - 1; j++)
        {
            if (column.at(j) == '0')
            {
                std::cout << "   |";
            }
            else if (column.at(j) == 'a')
            {
                std::cout << "A 1|";
            }
            else if (column.at(j) == 'b')
            {
                std::cout << "B 1|";
            }
            else if (column.at(j) == '-')
            {
                std::cout << " ~ |";
            }
        }
        if (column.at(columns_ - 1) == '0')
        {
            std::cout << "   " << std::endl;
        }
        else if (column.at(columns_ - 1) == 'a')
        {
            std::cout << "A 1" << std::endl;
        }
        else if (column.at(columns_ - 1) == 'b')
        {
            std::cout << "B 1" << std::endl;
        }
        else if (column.at(columns_ - 1) == '-')
        {
            std::cout << " ~ " << std::endl;
        }
    }

    // if (configFile.is_open())
    // {

    // for (int i = 0; i < rows_; ++i)
    // {
    //     // fields_[i].resize(columns_);
    //     for (int j = 0; j < columns_; ++j)
    //         {
    //             fields_[i][j] = new Field(nullptr, 0, false);
    //             std::cout << "1" << std::endl;
    //         }
    //         std::cout << "\n";
    //     }
    //     std::cout << rows_ << std::endl;
    // }
    // else
    // {
    //     std::cout << "Error: Unable to open config file." << std::endl;
    // }
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

void Map::setColumns(int columns)
{
    columns_ = columns;
}

int Map::getColumns()
{
    return columns_;
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
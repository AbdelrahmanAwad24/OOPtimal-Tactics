#include "Map.hpp"
#include <fstream>
#include <iostream>

Map::Map(char *config_path, Player *player_a, Player *player_b)
    : columns_(0), rows_(0), output_active_(false)
{
    // Initialize map components based on config_path
    std::ifstream configFile(config_path);
    if (configFile.is_open())
    {
        configFile >> rows_ >> columns_;
        fields_.resize(rows_);
        for (int i = 0; i < rows_; ++i)
        {
            fields_[i].resize(columns_);
            for (int j = 0; j < columns_; ++j)
            {
                fields_[i][j] = new Field(nullptr, 0, false);
            }
        }
        // configFile.close();
    }
    else
    {
        std::cerr << "Error: Unable to open config file." << std::endl;
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

void Map::setColumns(int columns)
{
    columns_ = columns;
}

int Map::getColumns()
{
    return 0;
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
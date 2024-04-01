#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include "Field.hpp"

class Map
{
private:
    int columns_;
    int rows_;
    std::vector<std::vector<Field *>> fields_;
    bool output_active_;
    int counter_;

public:
    Map(char *config_path, Player *player_a, Player *player_b);
    Map(const Map &other) = delete;
    Map() = default;
    ~Map();

    void printMap();
    void setColumns(int columns);
    int getColumns();
    void setCounter(int counter);
    int getCounter();
    void setRows(int rows);
    int getRows();
    void setFields(const std::vector<std::vector<Field *>> &fields);
    std::vector<std::vector<Field *>> &getFields();
    void setOutputActive(bool output_active);
    bool isOutputActive();
    void placeChips(int column, int row, int chips, Player *player);
};

#endif
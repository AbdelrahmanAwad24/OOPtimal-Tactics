// Command.hpp

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <string>

enum class CommandType
{
    PLACE,
    PASS,
    MOVE,
    MAP,
    INFO,
    QUIT,
    INVALID,
    WRONG_PARAM
};

class Command
{
private:
    CommandType type_;
    std::vector<std::string> parameters_;

public:
    // Constructors
    Command(std::vector<std::string> &input);
    Command(CommandType type);

    // Copy Constructor
    Command(const Command &other);

    // Destructor
    ~Command();

    // Methods
    bool isQuit();
    CommandType getType();
    std::vector<std::string> &getParameters();
    void setType(CommandType type);
};

#endif // COMMAND_HPP

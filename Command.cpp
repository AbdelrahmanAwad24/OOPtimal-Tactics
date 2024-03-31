
#include "Command.hpp"

// Constructor
Command::Command(std::vector<std::string> &input)
{
    if (input.empty())
    {
        type_ = CommandType::INVALID;
    }
    else
    {
        std::string commandTypeString = input[0];
        for (char &c : commandTypeString)
        {
            c = std::toupper(c);
        }
        if (commandTypeString == "PLACE")
        {
            type_ = CommandType::PLACE;
        }
        else if (commandTypeString == "PASS")
        {
            type_ = CommandType::PASS;
        }
        else if (commandTypeString == "MOVE")
        {
            type_ = CommandType::MOVE;
        }
        else if (commandTypeString == "MAP")
        {
            type_ = CommandType::MAP;
        }
        else if (commandTypeString == "INFO")
        {
            type_ = CommandType::INFO;
        }
        else if (commandTypeString == "QUIT")
        {
            type_ = CommandType::QUIT;
        }
        else
        {
            type_ = CommandType::INVALID;
        }

        // Store parameters
        for (size_t i = 1; i < input.size(); ++i)
        {
            parameters_.push_back(input[i]);
        }
    }
}

// Additional Constructor
Command::Command(CommandType type) : type_(type) {}

// Copy Constructor
Command::Command(const Command &other)
{
    type_ = other.type_;
    parameters_ = other.parameters_;
}

// Destructor
Command::~Command() {}

// Method to check if command is QUIT
bool Command::isQuit()
{
    return type_ == CommandType::QUIT;
}

// Getter for type_
CommandType Command::getType()
{
    return type_;
}

// Getter for parameters_
std::vector<std::string> &Command::getParameters()
{
    return parameters_;
}

// Setter for type_
void Command::setType(CommandType type)
{
    type_ = type;
}

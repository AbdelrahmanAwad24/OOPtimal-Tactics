#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <string>
#include "Map.hpp"
#include "Player.hpp"
#include "Command.hpp"
#include "CommandLine.hpp"

enum class Phase
{
    PLACEMENT,
    MOVEMENT,
    END
};

class Game
{
private:
    Map *map_;
    Player *player_a_;
    Player *player_b_;
    int current_round_;
    int max_rounds_;
    Phase phase_;
    Player *active_player_;
    static int toggle;
    static int toggle_flag;
    static int placement_header;
    static int placement_counter;
    static int movement_header;
    static int movement_counter;
    // static int saved_chips_a;
    // static int saved_chips_b;

public:
    Game(int maximum_rounds, char *config_path);
    Game(const Game &other) = delete;

    ~Game();

    static int getRoundNumber(char *string);
    static bool isValidRoundNumber(int rounds);
    static bool isValidConfig(char *config_path);
    void start();
    void execute(Command command);
    bool isRunning();

    // Getters and setters
    void intializeMap();
    Map *getMap();
    void setMap(Map *map);
    Player *getPlayerA();
    void setPlayerA(Player *player);
    Player *getPlayerB();
    void setPlayerB(Player *player);
    int getCurrentRound();
    void setCurrentRound(int round);
    int getMaxRounds();
    void setMaxRounds(int max_rounds);
    Phase getPhase();
    void setPhase(Phase phase);
    Player *getActivePlayer();
    void setActivePlayer(Player *player);
    void placmentPhase();
    void movementPhase();
    void toggleActivePlayer();
    void handleActivePlayer();
    void endGame();
    void handlePlace(Command command);
    void handleMove(Command command);
    void handlePass();
    void handleInfo();
};

#endif
#ifndef GAME_H
#define GAME_H
#include "Entity.h"
#include "Game.h"
#include "Room.h"


class Game {

    Room *first_room;
    Player *player;

public:
    //constructor
    Game(char player_type, int max_life, int damage, char *config_file_path);
    //destructor
    ~Game();
    // read config file
    void initGame(char *config_file_path);
    // game func
    void start();
};

#endif //GAME_H

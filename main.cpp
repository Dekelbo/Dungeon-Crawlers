#include "Game.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 5) { // check amount of args
        printf("Usage: %s  <> <max_life> <damage> <configurationFile>\n", argv[0]);
        return -1;
    }

    // get args
    char player_type = argv[1][0];
    int max_life = atoi(argv[2]);
    int damage = atoi(argv[3]);
    char *config_file_path = argv[4];

    Game *game = new Game(player_type,max_life, damage, config_file_path);
    game->start();
    delete game;
    return 0;
}

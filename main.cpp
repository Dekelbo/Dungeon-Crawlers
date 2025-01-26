#include "Game.h"
#include <iostream>
using namespace std;

void checkArgs(int max_life, int damage) {
    if(max_life < 0 || damage < 0) {
        throw invalid_argument("Invalid Value");
    }
}

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

    try {
        checkArgs(max_life, damage);
    } catch(invalid_argument &e) {
        cout << e.what() << endl;
        return -1;
    }

    Game *game;

    try {
       game = new Game(player_type,max_life, damage, config_file_path);
    } catch(invalid_argument &e) {
        cout << e.what() << endl;
        delete game;
        return -1;
    }
    catch(bad_alloc &e) {
        cout << e.what() << endl;
        delete game;
        return -1;
    }

    game->start();
    delete game;
    return 0;
}

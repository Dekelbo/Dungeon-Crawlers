#include "Game.h"
#include <cstring>
#include <ostream>
#include <iostream>

#include "Fighter.h"
#include "Sorcerer.h"
using namespace std;

//constructor
Game::Game(char player_type, int max_life, int damage, char *config_file_path) {
    if(player_type == 'F') {
        this->player = new Fighter(max_life, damage); // player is fighter
    }
    else if(player_type == 'S') {
        this->player = new Sorcerer(max_life, damage); // player is sorcerer
    }

    char tmp_id[] = "-1";
    this->first_room = new Room(tmp_id, 0,'N', 0, 0);
    this->initGame(config_file_path);
}

//destructor
Game::~Game() {
    delete this->player;
    delete this->first_room;
}


// read config file
void Game:: initGame(char *config_file_path) {

    // max lengh of line
    int MAX_LINE_LENGTH = 256;
    // open file
    FILE *config_file = fopen(config_file_path, "r");

    if (config_file == NULL) {
        printf("Config file is NULL\n");
        fclose(config_file);
    }

    char line[MAX_LINE_LENGTH];

    //create and store rooms

    char *linecheck = fgets(line, MAX_LINE_LENGTH, config_file); // example: 10 0 D 20 10


    while (linecheck != nullptr && linecheck[0] != '\n')
    {
        char id[MAX_LINE_LENGTH];
        int fire;
        char monster_type;
        int monster_max_life;
        int damage;

        int parsed = sscanf(line, "%255s %d %c", id, &fire, &monster_type);
        if (parsed != 3) {
            printf("Error parsing configuration file1\n");
            fclose(config_file);
        }

        // there is a monster
        if(monster_type == 'D' || monster_type == 'G') {
            parsed = sscanf(line, "%255s %d %c %d %d", id, &fire, &monster_type, &monster_max_life, &damage);
            if (parsed != 5) {
                printf("Error parsing configuration file2\n");
                fclose(config_file);
            }
        }

        // no monster - Room responsible to put nullptr in Monster
        else if(monster_type == 'N') {
            monster_max_life = -1;
            damage = -1;
        }

        //new room
        Room *room = new Room(id, fire, monster_type ,monster_max_life, damage);

        //accesses to room
        int id_len = strlen(id);
        Room* current_room = first_room;

        //find the room that should have access to the new room
        for (int i = 0; i < id_len-1; i++)
        {
            int current_digit = id[i] - '0';
            try {
                current_room = &((*current_room)[current_digit]);
            }
            catch () {
            }
        }

        // Add the new room to the appropriate subroom
        int index = id[strlen(id)-1]- '0';
        (*current_room)[index] = *room;

        linecheck = fgets(line, MAX_LINE_LENGTH, config_file);
        delete(room);
    }

    //close file
    fclose(config_file);
}

enum fight_status {
    KEEP_PLAYING,
    END_ROUND,
    END_GAME
};

fight_status fightRound(Player &player, Monster &monster)
{
    // player attacks
    cout << "You deal " << player.attack() << " damage to the " << monster.getName() << " and leave it with " << monster.getCurrentLife() << " health" << endl;

    // monster loses
    if(monster.getCurrentLife() == 0) {
        cout << "You defeat the " << monster.getName() << " and go on with your journey" << endl;
        return END_ROUND;
    }

    // monster attacks
    cout << "The " << monster.getName() << " deals " << monster.attack() << " damage to you and leaves you with " << player.getCurrentLife() << " health" << endl;

    // player loses
    if(player.getCurrentLife() == 0)
    {
        cout << "You lost to the dungeon" << endl;
        return END_GAME;
    }

    return KEEP_PLAYING;
}

// game func
void Game:: start() {
    int input;
    cout << *this->player << endl;

    // first room
    Room* current_room = first_room;

    // the game loop
    while (true)
    {
        // monster and fire in the room
        Monster *current_monster = current_room->getMonster();
        int fire = current_room->getFire();

        if(current_room->isEmpty())
        {
            cout << "You arrive to an empty room" << endl;
        }

        // room is not empty
        else {
            if(fire != 0){
                cout << "You sit by the campfire and heal " << fire << " health" << endl;
                *this->player += fire;

                // update turn for special power
                this->player->updateTurn();
            }


            // encountering a monster
            if(current_monster != nullptr)
            {
                // tell the player and the monster who they are fighting
                this->player->set_fighting_who(current_monster);
                current_monster->set_fighting_who(this->player);

                //player is stronger
                if(*this->player > *current_monster)
                {
                    cout << "You encounter a smaller " << current_monster->getName() << endl;
                }

                // equal
                else if(*this->player == *current_monster)
                {
                    cout << "You encounter a equally sized " << current_monster->getName() << endl;
                }

                // monster is stronger
                else
                {
                    cout << "You encounter a larger " << current_monster->getName() << endl;
                }

                cout << *current_monster << endl;

                // fight until one of them dies
                fight_status status = KEEP_PLAYING;
                while(status == KEEP_PLAYING) {
                    status = fightRound(*this->player, *current_monster);
                }

                // player lost
                if(status == END_GAME) {
                    break;
                }

                // otherwise player beat the monster and status is END_ROUND, continue to next room
            }
        }

        // won entire game
        if(current_room->isLastRoom())
        {
            cout << "The room continues and opens up to the outside. You won against the dungeon" << endl;
            break;
        }

        // only 1 option for next room
        if(current_room->getEstimatedCountOfRooms() == 1)
        {
            cout << "You see a single corridor ahead of you labeled 0" << endl;
            cin >> input;
        }

        // choose next room
        else
        {
            int last_room_index = current_room->getEstimatedCountOfRooms() - 1 ;
            cout << "You see corridors labeled from 0 to " << last_room_index << ". Which one will you choose?" << endl;
            cin >> input;
        }

        //enter next room
        current_room = &(*current_room)[input];

        // update turn for special power
        this->player->updateTurn();

        cout << *this->player << endl;
    }

}

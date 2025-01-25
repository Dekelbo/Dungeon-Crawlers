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
            monster_max_life = 0;
            damage = 0;
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
            current_room = &((*current_room)[current_digit]);
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

// game func
void Game:: start() {
    int input;
    cout << *this->player << endl;
    cout << "I see you like challenges, by how much do you want to reduce your damage?" << endl;
    cin >> input;

    //new damage of player
    this->player->setDamage(this->player->getDamage() - input);
    cout << *this->player << endl;

    //first room
    Room* current_room = first_room;

    // the game loop
    while(true)
    {
        // monster and fire in current room
        int fire = current_room->getFire();
        int mon_life = current_room->getMonster()->getCurrentLife();

        if(current_room->isEmpty())
        {
            cout << "You arrive to an empty room" << endl;
        }

        // room is not empty
        else {

            if(fire != 0){
                cout << "You sit by the campfire and heal " << fire << " health" << endl;
                *this->player += fire;
            }

            // encountering a monster
            else if(mon_life != 0)
            {
                //player is stronger
                if(*this->player > *current_room->getMonster())
                {
                    cout << "You encounter a smaller monster" <<endl;
                }

                // equal
                else if(*this->player == *current_room->getMonster())
                {
                    cout << "You encounter a equally sized monster" <<endl;
                }

                // monster is stronger
                else
                {
                    cout << "You encounter a larger monster" <<endl;
                }

                cout << *current_room->getMonster() << endl;

                //fight

                //player attacks
                *current_room->getMonster() -= *this->player;
                cout << "You deal " << this->player->getDamage() << " damage to the monster and leave it with " << current_room->getMonster()->getCurrentLife() << " health" << endl;

                if(current_room->getMonster()->getCurrentLife() != 0)
                {
                    //monster attacks
                    *this->player -= *current_room->getMonster();
                    cout << "The monster deals " << current_room->getMonster()->getDamage() << " damage to you and leaves you with " << this->player->getCurrentLife() << " health" << endl;

                    //player loses
                    if(this->player->getCurrentLife() == 0)
                    {
                        cout << "You lost to the dungeon" << endl;
                        break;
                    }
                }

                cout << "You defeat the monster and go on with your journey" << endl;
            }
        }

        //player continues to next room

        //win
        if(current_room->isLastRoom())
        {
            cout << "The room continues and opens up to the outside. You won against the dungeon" << endl;
            break;
        }

        //only 1 next room
        if(current_room->getEstimatedCountOfRooms() == 1)
        {
            cout << "You see a single corridor ahead of you labeled 0" << endl;
            cin >> input;
        }

        //choose next room
        else
        {
            int last_room_index = current_room->getEstimatedCountOfRooms() - 1 ;
            cout << "You see corridors labeled from 0 to " << last_room_index << ". Which one will you choose?" << endl;
            cin >> input;
        }

        //enter next room
        current_room = &(*current_room)[input];
        cout << *this->player << endl;
    }

}

#include "Room.h"
#include <iostream>
#include <cstring>

#include "Dragon.h"
#include "Goblin.h"

using namespace std;

// Default Constructor
Room::Room() {
    this->id = strdup("-1");
    this->fire = -1;
    this->monster = new Dragon(-1, -1); //TODO: nullptr ?
    this->roomCount = 0;
    this->estimated_count_of_rooms = 0;
    this->rooms = nullptr;
}

// Constructor
Room::Room(const char *id, int fire,char monster_type, int monster_life, int monster_damage) {
    this->id = strdup(id);
    this->fire = fire;
    if (monster_type == 'D') {
        this->monster = new Dragon(monster_life, monster_damage);
    }
    else if (monster_type == 'G') {
        this->monster = new Goblin(monster_life, monster_damage);
    }

    else {
        this->monster = nullptr;
    }

    this->roomCount = 0;
    this->estimated_count_of_rooms = 0;
    this->rooms = nullptr;
}

// Copy Constructor
Room::Room(const Room& other) {
    this->id = strdup(other.id);
    this->fire = other.fire;
    this->roomCount = other.roomCount;
    if (strcmp(other.getMonster()->getName(),"Dragon") == 0) {
        this->monster = new Dragon(*static_cast<Dragon*>(other.monster));
    }
    else if (strcmp(other.getMonster()->getName(),"Goblin") == 0) {
        this->monster = new Goblin(*static_cast<Goblin*>(other.monster));
    }
    else {
        this->monster = nullptr;
    }

    this->estimated_count_of_rooms = 0;
    if (other.rooms) {
        this->rooms = new Room[other.estimated_count_of_rooms];
        for (int i = 0; i < other.estimated_count_of_rooms; ++i) {
            this->rooms[i] = other.rooms[i];
        }
    } else {
        this->rooms = nullptr;
    }
}

// Destructor
Room::~Room() {

    delete[] this->rooms;
    free(this->id);
    delete this->monster;

}


//assign a room to rooms array in last digit of id cell
Room &Room::operator=(const Room &other) {
    if (this == &other) {
        return *this;
    }

    // Free this
    if (this->id) {
        free(this->id);
    }
    if (this->monster) {
        delete this->monster;
    }
    if (this->rooms) {
        delete[] this->rooms;
    }

    this->id = strdup(other.id);
    this->fire = other.fire;
    this->roomCount = other.roomCount;
    this->estimated_count_of_rooms = other.estimated_count_of_rooms;

    // Deep copy the monster
    if (other.monster) {
        this->monster = new Entity(*other.monster);
    } else {
        this->monster = nullptr;
    }

    if (other.rooms) {
        this->rooms = new Room[other.estimated_count_of_rooms];
        for (int i = 0; i < other.estimated_count_of_rooms; i++) {
            this->rooms[i] = other.rooms[i]; // Recursive deep copy
        }
    } else {
        this->rooms = nullptr;
    }

    return *this;
}

//operator[] to give access to assign a room
Room& Room::operator[](int index) {

    if (index >= this->estimated_count_of_rooms)
    {
        int old_count = this->estimated_count_of_rooms;
        this->estimated_count_of_rooms = index + 1;
        this->roomCount++;

        Room* temp = new Room[this->estimated_count_of_rooms];
        for (int i = 0; i < old_count; ++i) {
            temp[i] = this->rooms[i]; // Deep copy old rooms
        }
        delete[] this->rooms;
        this->rooms = temp;

    }

    // Initialize a new room if it doesn't exist
    if (strcmp(this->rooms[index].id, "-1") == 0) {
        this->rooms[index] = Room(); // Create a new room
    }

    return this->rooms[index];
}

//operator[] read only
const Room &Room:: operator[](int index) const {
    return this->rooms[index];
}

// Getter for id
const char* Room::getId() const {
    return id;
}

// Getter for fire
int Room::getFire() const {
    return fire;
}

// Getter for monster
Entity *Room::getMonster() const {
    return this->monster;
}

// Getter for rooms array
Room* Room::getRooms() const {
    return rooms;
}

// Getter for estimated count of rooms
int Room::getEstimatedCountOfRooms() const {
    return estimated_count_of_rooms;
}

//true if empty room
bool Room::isEmpty() const {
    return (this->getFire() == 0 && this->monster->getCurrentLife() == 0);
}

//true if no access to other rooms
bool Room::isLastRoom() const {
    return this->rooms == nullptr;
}
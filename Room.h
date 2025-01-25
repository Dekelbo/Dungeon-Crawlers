#ifndef ROOM_H
#define ROOM_H
#include "Entity.h"

class Room {

    char *id;            //room number
    int fire;           // 0 means no fire
    Room* rooms;        // array of Room pointers
    int roomCount;      // Current number of rooms in array
    int estimated_count_of_rooms; // count of rooms - will be filled in the end of config file
    Entity *monster;

public:

    // Default Constructor
    Room();

    // Constructor
    Room(const char *id, int fire, char monster_type, int monster_life, int monster_damage);

    // Copy Constructor
    Room(const Room& other);

    // Destructor
    ~Room();

    //assign a room to rooms array in last digit of id cell
    Room &operator=(const Room &other);

    //operator[] to give access to assign a room
    Room& operator[](int index);

    //operator[] read only
    const Room& operator[](int index) const;

    // Getter for id
    const char* getId() const;

    // Getter for rooms array
    Room* getRooms() const;

    // Getter for estimated count of rooms
    int getEstimatedCountOfRooms() const;

    // Getter for monster
    Entity *getMonster() const;

    // Getter for fire
    int getFire() const;

    //true if empty room
    bool isEmpty() const;

    //true if no access to other rooms
    bool isLastRoom() const;
};

#endif //ROOM_H

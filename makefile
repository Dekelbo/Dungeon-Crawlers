all: main

main: Entity.o Room.o Game.o main.o
	g++ -Wall -g -o Dungeon Entity.o Room.o Game.o main.o

Entity.o: Entity.cpp Entity.h
	g++ -Wall -g -c Entity.cpp -o Entity.o

Room.o: Room.cpp Room.h
	g++ -Wall -g -c Room.cpp -o Room.o

Game.o: Game.cpp Game.h
	g++ -Wall -g -c Game.cpp -o Game.o

main.o: main.cpp
	g++ -Wall -g -c main.cpp -o main.o

clean:
	rm -f *.o Dungeon

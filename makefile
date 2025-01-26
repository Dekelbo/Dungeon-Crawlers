all: Dungeon

Dungeon: Entity.o Room.o Game.o main.o Goblin.o Dragon.o Monster.o Player.o Fighter.o Sorcerer.o
	g++ -Wall -g -o Dungeon Entity.o Room.o Game.o main.o Goblin.o Dragon.o Monster.o Player.o Fighter.o Sorcerer.o

Entity.o: Entity.cpp Entity.h
	g++ -Wall -g -c Entity.cpp -o Entity.o

Room.o: Room.cpp Room.h
	g++ -Wall -g -c Room.cpp -o Room.o

Game.o: Game.cpp Game.h
	g++ -Wall -g -c Game.cpp -o Game.o

Goblin.o: Goblin.cpp Goblin.h Monster.h
	g++ -Wall -g -c Goblin.cpp -o Goblin.o

Dragon.o: Dragon.cpp Dragon.h Monster.h
	g++ -Wall -g -c Dragon.cpp -o Dragon.o

Monster.o: Monster.cpp Monster.h
	g++ -Wall -g -c Monster.cpp -o Monster.o

Player.o: Player.cpp Player.h Entity.h
	g++ -Wall -g -c Player.cpp -o Player.o

Fighter.o: Fighter.cpp Fighter.h Player.h
	g++ -Wall -g -c Fighter.cpp -o Fighter.o

Sorcerer.o: Sorcerer.cpp Sorcerer.h Player.h
	g++ -Wall -g -c Sorcerer.cpp -o Sorcerer.o

main.o: main.cpp
	g++ -Wall -g -c main.cpp -o main.o

clean:
	rm -f *.o Dungeon


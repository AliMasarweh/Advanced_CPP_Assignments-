a.out: main.o Card.o Player.o Game.o
	g++ -o a.out main.o Card.o Player.o Game.o
main.o: main.cpp Game.h
	g++ -c main.cpp
Card.o: Card.cpp Card.h
	g++ -c Card.cpp
Player.o: Player.cpp Player.h Card.h
	g++ -c Player.cpp
Game.o: Game.cpp Game.h Player.h Card.h
	g++ -c Game.cpp
clean:
	rm a.out main.o Card.o Player.o Game.o
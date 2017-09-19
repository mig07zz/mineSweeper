all: minesweeper_game

minesweeper_game: main.o mineSweeper.o
	g++ main.o mineSweeper.o -o minesweeper_game
	
main.o: main.cpp
	g++ -c main.cpp
	
mineSweeper.o: mineSweeper.cpp
	g++ -c mineSweeper.cpp
	
clean:
	rm -rf *o minesweeper_game

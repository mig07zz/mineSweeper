all: minesweeper_game

minesweeper_game: main.o mineSweeper.o
	g++ main.o mineSweeper.o -o minesweeper_game
	
main.o: main.cpp
	g++ -c -std=c++11 main.cpp
	
mineSweeper.o: mineSweeper.cpp
	g++ -c -std=c++11 mineSweeper.cpp
	
clean:
	rm -rf *o minesweeper_game

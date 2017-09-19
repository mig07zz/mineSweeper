#include <iostream>
#include "mineSweeper.h"
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <stdio.h>

using namespace std;

// extern Board * GAMEBOARD = NULL;


mineSweeper::mineSweeper(){
    board_width = 10;
    board_height = 10;
    srand(time(NULL));
}

mineSweeper::~mineSweeper(){}


int mineSweeper::gen_rand_num(int max){

    return rand() % max;
}

Board_t * mineSweeper::make_gameBoard(int width, int height){
    int size = width * height;
    Board_t * GAMEBOARD = (Board_t*)malloc(size*sizeof(Board_t));
    for (int i = 0; i<size;i++){GAMEBOARD[i] = 0;}
    
    int bomb_limit =  (int)ceil(((float)size * .20));
    for (int i =0 ;i<bomb_limit;i++){
        GAMEBOARD[gen_rand_num(size)] = 1;
    }

    return GAMEBOARD;
    
}
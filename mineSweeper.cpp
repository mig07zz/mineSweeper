#include <iostream>
#include "mineSweeper.h"
#include <cstdlib>
#include <time.h>
#include <math.h>

using namespace std;


mineSweeper::mineSweeper(){
    board_width = 10;
    board_height = 10;
    srand(time(NULL));
}

mineSweeper::~mineSweeper(){}

// int mineSweeper::gen_rand_num(int max,int seed);

int mineSweeper::gen_rand_num(int max){
    // srand((unsigned)seed);
    return rand() % max;
}

Board * mineSweeper::make_gameBoard(int width, int height){
    int size = width * height;
    Board gameBoard [size];
    for (int i = 0; i<size;i++){gameBoard[i] = 0;}
    int bomb_limit =  (int)ceil(((float)size * .15));
    cout<<bomb_limit<<endl;
    
    for (int i =0 ;i<bomb_limit;i++){
        gameBoard[gen_rand_num(size)] = 1;
    }
    for (int i = 0; i<size;i++){
        if (!(i%width)){cout<<endl;}
        cout<<(int)gameBoard[i];
        
    }
    cout<<endl;
    
    
    
    Board *ptrBoard = gameBoard;
    return ptrBoard;
    
}
#include <iostream>
#include "mineSweeper.h"
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <algorithm>

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

Board_t * mineSweeper::make_gameBoard(int width, int height,int number_of_mines){
    
    int size = width * height;
    Board_t * GAMEBOARD = (Board_t*)malloc(size*sizeof(Board_t));
    for (int i = 0; i<size;i++){GAMEBOARD[i] = 0;}
    
    // int bomb_limit =  (int)ceil(((float)size * .20));
    int bomb_limit = max(number_of_mines,1);
    if (bomb_limit>size){
        bomb_limit = min(size,number_of_mines);
    }
    
    for (int i =0 ;i<bomb_limit;i++){
        GAMEBOARD[gen_rand_num(size)] = 1;
    }

    return GAMEBOARD;
    
}

void mineSweeper::init_board(SQUARE_t *outerBoard,Board_t *innerBoard){
    cout<<endl<<"this is innerboard[1]"<<(int)innerBoard[1]<<endl;
    for (int i = 0; i< (this->board_height*this->board_width);i++){
        outerBoard[i].val = '#';
        outerBoard[i].open = false;
        outerBoard[i].flagged = false;
        outerBoard[i].neighbor_mines = -1;
        if (innerBoard[i]==1){
            outerBoard[i].secret = '*';
        }
        else{
            outerBoard[i].secret = '~';
        }
    }
}

void mineSweeper::displayBoard(SQUARE_t *theBoard){
    cout<<"======================================================"<<endl;
    int endofline = this->board_width;
    int b_size = this->board_height*this->board_width;
    for (int i = 0; i<b_size;i++){
        if(!(i%endofline)){cout<<endl;}
        cout<<theBoard[i].val;
    }
    cout<<endl<<"========================================================"<<endl;
}

void mineSweeper::calc_hidden(SQUARE_t *theBoard){
    
}

bool mineSweeper::has_top_n(int center_x,int center_y){
    return ((center_y - 1) >= 0)?true:false;
}
bool mineSweeper::has_bottom_n(int center_x,int center_y){
    return ((center_y+1)<this->board_height)?true:false;
}
bool mineSweeper::has_left_n(int center_x,int center_y){
    return ((center_x-1)>=0)?true:false;
}
bool mineSweeper::has_right_n(int center_x,int center_y){
    return ((center_x+1)<this->get_width())?true:false;
}
bool mineSweeper::has_topRight_n(int center_x,int center_y){
    return ((center_x+1)<this->get_width())&((center_y-1)>=0)?true:false;
}
bool mineSweeper::has_topLeft_n(int center_x,int center_y){
    return ((center_x-1)>=0)&((center_y-1)>=0)?true:false;
}
bool mineSweeper::has_bottomRight_n(int center_x,int center_y){
    return ((center_x+1)<this->get_width())&((center_y+1)<this->get_height())?true:false;
}
bool mineSweeper::has_bottomLeft_n(int center_x,int center_y){
    return ((center_x-1)>=0)&((center_y+1)<this->get_height())?true:false;
}

//getters 
int mineSweeper::get_height(){return this->board_height;}
int mineSweeper::get_width(){return this->board_width;}


//setters
void mineSweeper::set_height(int h){this->board_height = h;}
void mineSweeper::set_width(int w){this->board_width = w;}

#include <iostream>
#include "mineSweeper.h"
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <string.h>

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
int mineSweeper::coor_to_index(int x, int y){
    return y*this->board_width+x;
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
    // cout<<endl<<"this is innerboard[1]"<<(int)innerBoard[1]<<endl;
    for (int i = 0; i< (this->board_height*this->board_width);i++){
        outerBoard[i].val = '#';
        outerBoard[i].open = false;
        outerBoard[i].flagged = false;
        outerBoard[i].neighbor_mines = 0;
        if (innerBoard[i]==1){
            outerBoard[i].secret = '*';
        }
        else{
            outerBoard[i].secret = '~';
        }
        outerBoard[i].x = i%this->board_width;
        outerBoard[i].y = i/this->board_height;
    }
    calc_hidden(outerBoard);
}

void mineSweeper::displayBoard(SQUARE_t *theBoard){
    cout<<"======================================================"<<endl;
    int endofline = this->board_width;
    int b_size = this->board_height*this->board_width;
    for (int i = 0; i<b_size;i++){
        if(!(i%endofline)){cout<<endl;}
        cout<<" "<<theBoard[i].val;
    }
    cout<<endl<<"========================================================"<<endl;
    
    //below this line is just for testing. Needs to be removed on the final version.================================================================================
    //     for (int i = 0; i<b_size;i++){
    //     if(!(i%endofline)){cout<<endl;}
    //     cout<<" "<<theBoard[i].secret;
    // }
    // cout<<endl<<"========================================================"<<endl;
    //     for (int i = 0; i<b_size;i++){
    //     if(!(i%endofline)){cout<<endl;}
    //     cout<<" "<<theBoard[i].neighbor_mines;
    // }
    // cout<<endl<<"========================================================"<<endl;
}
void mineSweeper::displayAll(SQUARE_t *theboard){
    cout<<"======================================================"<<endl;
    int endofline = this->board_width;
    int b_size = this->board_height*this->board_width;
    for (int i = 0; i<b_size;i++){
        if(!(i%endofline)){cout<<endl;}
        cout<<" "<<theboard[i].secret;
    }
    cout<<endl<<"========================================================"<<endl;
}

void mineSweeper::calc_hidden(SQUARE_t *theBoard){
    int w = this->board_width;
    int h = this->board_height;
    int x = 0;
    int y = 0;
    for (;y<h;y++){
        x = 0;
        for(;x<w;x++){
            mineFinder(theBoard,x,y); 
            // cout<<coor_to_index(x,y)<<endl;
        }
    }
}


void mineSweeper::mineFinder(SQUARE_t* theboard,int x, int y){
    if (has_top_n(x,y)){
        if(theboard[coor_to_index(x,y-1)].secret == '*'){
            theboard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_bottom_n(x,y)){
        if(theboard[coor_to_index(x,y+1)].secret == '*'){
            theboard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_left_n(x,y)){
        if(theboard[coor_to_index(x-1,y)].secret == '*'){
            theboard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_right_n(x,y)){
        if(theboard[coor_to_index(x+1,y)].secret == '*'){
            theboard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_topLeft_n(x,y)){
        if(theboard[coor_to_index(x-1,y-1)].secret == '*'){
            theboard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_topRight_n(x,y)){
        if(theboard[coor_to_index(x+1,y-1)].secret == '*'){
            theboard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_bottomLeft_n(x,y)){
        if(theboard[coor_to_index(x-1,y+1)].secret == '*'){
            theboard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_bottomRight_n(x,y)){
        if(theboard[coor_to_index(x+1,y+1)].secret == '*'){
            theboard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
}

void mineSweeper::open_square(SQUARE_t * theboard,int x,int y,bool &gameOver){
    int index = coor_to_index(x,y);
    if (theboard[index].secret=='*'){
        gameOver = true;
        theboard[index].val = theboard[index].secret;
        theboard[index].open = true;
    }
    else{
        theboard[index].val = '0'+theboard[index].neighbor_mines;
        theboard[index].open = true;
    }
    
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

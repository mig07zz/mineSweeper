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
    bomb_check = 0;
    flag_num = 0;
    bomb_counter = 100; // number of uncovered spaces
    srand(time(NULL));
}

mineSweeper::~mineSweeper(){}

// void mineSweeper::handle_player_turn(char c){
//     string x_coor;
//     string y_coor;
//     switch (c){
//         case '1':
//             cout<<"\nenter x coordinate to open.==>";
//             cin>>x_coor;
//             cout<<"\nenter y coordinate to open.==>";
//             cin>>y_coor;
//             int clean_x =  validate_numbers(x_coor);
//             int clean_y =  validate_numbers(y_coor);
//             open_square(this,clean_x,clean_y,gameOver);
//         break;
//         case '2':
//             cout<<"\nenter x coordinate to flag.==>";
//             cin>>x_coor;
//             cout<<"\nenter y coordinate to flag.==>";
//             cin>>y_coor;
//             int clean_x =  validate_numbers(x_coor);
//             int clean_y =  validate_numbers(y_coor);
//             toggle_flag_square(this,clean_x,clean_y,gameOver);
//         break;
//         case '3':
//             cout<<"\nenter x coordinate to remove flag.==>";
//             cin>>x_coor;
//             cout<<"\nenter y coordinate to remove flag.==>";
//             cin>>y_coor;
//             int clean_x =  validate_numbers(x_coor);
//             int clean_y =  validate_numbers(y_coor);
//             toggle_flag_square(this,clean_x,clean_y,gameOver);
//         break;
//         default:
//     }

// }
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
    init_bomb_counter();
    set_bomb_check(outerBoard);
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
    //     cout<<" "<<theBoard[i].open;
    // }
//     cout<<endl<<"========================================================"<<endl;
//         for (int i = 0; i<b_size;i++){
//         if(!(i%endofline)){cout<<endl;}
//         cout<<" "<<theBoard[i].neighbor_mines;
//     }
//     cout<<endl<<"========================================================"<<endl;
}


void mineSweeper::displayAll(SQUARE_t *theBoard){
    cout<<"======================================================"<<endl;
    int endofline = this->board_width;
    int b_size = this->board_height*this->board_width;
    for (int i = 0; i<b_size;i++){
        if(!(i%endofline)){cout<<endl;}
        cout<<" "<<theBoard[i].secret;
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


void mineSweeper::mineFinder(SQUARE_t* theBoard,int x, int y){
    if (has_top_n(x,y)){
        if(theBoard[coor_to_index(x,y-1)].secret == '*'){
            theBoard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_bottom_n(x,y)){
        if(theBoard[coor_to_index(x,y+1)].secret == '*'){
            theBoard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_left_n(x,y)){
        if(theBoard[coor_to_index(x-1,y)].secret == '*'){
            theBoard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_right_n(x,y)){
        if(theBoard[coor_to_index(x+1,y)].secret == '*'){
            theBoard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_topLeft_n(x,y)){
        if(theBoard[coor_to_index(x-1,y-1)].secret == '*'){
            theBoard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_topRight_n(x,y)){
        if(theBoard[coor_to_index(x+1,y-1)].secret == '*'){
            theBoard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_bottomLeft_n(x,y)){
        if(theBoard[coor_to_index(x-1,y+1)].secret == '*'){
            theBoard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
    if (has_bottomRight_n(x,y)){
        if(theBoard[coor_to_index(x+1,y+1)].secret == '*'){
            theBoard[coor_to_index(x,y)].neighbor_mines +=1;
        }
    }
}

void mineSweeper::open_square(SQUARE_t * theBoard,int x,int y,bool &gameOver){
    int index = coor_to_index(x,y);
    if(theBoard[index].flagged){
        cout << "\nCan't open this space, there's a flag here! \n";
        return;
    }
    if (theBoard[index].secret=='*'){
        gameOver = true;
        theBoard[index].val = theBoard[index].secret;
        theBoard[index].open = true;
    }
    else{
        if (theBoard[index].neighbor_mines == 0){
            cout <<"found a square with a 0"<<endl;
            open_all_empty_neighbours(theBoard,x,y);
        }
        theBoard[index].val = '0'+theBoard[index].neighbor_mines;
        theBoard[index].open = true;
    }
    set_bomb_counter(theBoard);    
}

void mineSweeper::open_all_empty_neighbours(SQUARE_t * theBoard, int x, int y){
    // cout <<"x == "<<x<<"y == "<<y<<endl;
    int index = coor_to_index(x,y);
    if (theBoard[index].open ==true){
        return;
    }
    else{
        if (theBoard[index].neighbor_mines == 0&&theBoard[index].secret == '~'){
            theBoard[index].val = '0';
            theBoard[index].open = true;
            // set_bomb_counter();
        }
    }

    if (theBoard[index].neighbor_mines!=0&&theBoard[index].secret == '~'){
        theBoard[index].open == true;
        theBoard[index].val = '0'+theBoard[index].neighbor_mines;
        // set_bomb_counter();
        return;
    }
    if (has_top_n(x,y)){
        // cout<<"this square has top."<<endl;
        open_all_empty_neighbours(theBoard, x,y-1);
    }
    if (has_bottom_n(x,y)){
        // cout<<"this square has bottom."<<endl;
        open_all_empty_neighbours(theBoard,x,y+1);
    }
    if (has_left_n(x,y)){
                // cout<<"this square has left."<<endl;

        open_all_empty_neighbours(theBoard,x-1,y);
    }
    if(has_right_n(x,y)){
                // cout<<"this square has right."<<endl;

        open_all_empty_neighbours(theBoard,x+1,y);
    }
    if(has_topLeft_n(x,y)){
                // cout<<"this square has topleft."<<endl;

        open_all_empty_neighbours(theBoard,x-1,y-1);
    }
    if(has_topRight_n(x,y)){
                // cout<<"this square has topright."<<endl;

        open_all_empty_neighbours(theBoard,x+1,y-1);
    }
    if(has_bottomLeft_n(x,y)){
                // cout<<"this square has bottomleft."<<endl;

        open_all_empty_neighbours(theBoard,x-1,y+1);
    }
    if(has_bottomRight_n(x,y)){
                // cout<<"this square has bottomright."<<endl;

        open_all_empty_neighbours(theBoard,x+1,y+1);
    }
    return;
    
}

void mineSweeper::set_flag_square(SQUARE_t * theBoard,int x,int y,bool state){
    int index = coor_to_index(x, y);
    if(theBoard[index].open){
        cout << "\nWhy would you put a flag here? The space is already open!\n";
        return;
    }
    if(state){
        if(this->flag_num == 0){
            cout << "\nNo flags left!";
            return;
        }
        if(!theBoard[index].flagged){
            theBoard[index].flagged = state;
            theBoard[index].val = '!';
            this->flag_num--;
            cout << this->flag_num;
        }
        else{
            cout << "\nThere's already a flag here!";
        }
    }
    else{
        if(theBoard[index].flagged){
            theBoard[index].flagged = state;
            theBoard[index].val = '#';
            this->flag_num++;
            cout << this->flag_num;
        }
        else{
            cout << "\nThere's no flag here!";
        }
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
int mineSweeper::get_bomb_check(){
    return this->bomb_check;
}
int mineSweeper::get_bomb_counter(){
    return this->bomb_counter;
}

//setters
void mineSweeper::set_height(int h){this->board_height = h;}
void mineSweeper::set_width(int w){this->board_width = w;}
void mineSweeper::set_bomb_check(SQUARE_t *theBoard){
    int size = this->board_height * this->board_width;
    for (int i = 0;i<size;i++){
        if(theBoard[i].secret == '*'){
            this->bomb_check +=1;
        }
    }
    this->flag_num = this->bomb_check;
}

void mineSweeper::set_bomb_counter(SQUARE_t * theBoard){
    int size = this->board_height * this->board_width;
    this->bomb_counter = 0;
    for (int i = 0;i<size;i++){
        if(theBoard[i].val == '#' || theBoard[i] == '!'){
            this->bomb_counter +=1;
        }
    } 
}

void mineSweeper::init_bomb_counter(){
    this->bomb_counter = this->board_width*this->board_height;
}

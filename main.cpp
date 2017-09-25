#include <iostream>
#include <cstdlib>
#include "mineSweeper.h"
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>


using namespace std;
bool is_number(const string &s);
int validate_numbers(string s);


bool is_number(const std::string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int validate_numbers(string s){
  int ssize = s.size();
  if (ssize > 2 || (!is_number(s))){   //this is just a restriction to keep users from going over '99' 
    return MIN_BOARD_SZ;
  }
  else{
    if (is_number(s)){                      
      return stoi(s);
    }
  }
  return 1;
}

int handle_player_turn(char c,int *x,int * y){
    string x_coor;
    string y_coor;
    switch (c){
        case '1':
            cout<<"\nenter x coordinate to open.==>";
            cin>>x_coor;
            cout<<"\nenter y coordinate to open.==>";
            cin>>y_coor;
            *x =  validate_numbers(x_coor);
            *y =  validate_numbers(y_coor);

            // open_square(this,clean_x,clean_y,gameOver);
            return 1;
        break;
        case '2':
            cout<<"\nenter x coordinate to flag.==>";
            cin>>x_coor;
            cout<<"\nenter y coordinate to flag.==>";
            cin>>y_coor;
            *x =  validate_numbers(x_coor);
            *y =  validate_numbers(y_coor);
            // toggle_flag_square(this,clean_x,clean_y,gameOver);
            return 2;
        break;
        case '3':
            cout<<"\nenter x coordinate to remove flag.==>";
            cin>>x_coor;
            cout<<"\nenter y coordinate to remove flag.==>";
            cin>>y_coor;
            *x =  validate_numbers(x_coor);
            *y =  validate_numbers(y_coor);
            // toggle_flag_square(this,clean_x,clean_y,gameOver);
            return 3;
        break;
        default:
        return 0;
    }
    return 0;

}
 
int main(int argc, char *argv[])
{
  
  
  // validate_numbers("hello world..");
  int w = 10;
  int h = 10;
  int bombs = (int)ceil(((float)(w*h) * .20));   //default to 20% bombs
  
  if(argc>1){
    w = validate_numbers((argv[1]));
    // cout<<"here1"<<endl;
  }
  if(argc>2){
    h = validate_numbers((argv[2]));
        // cout<<"here2"<<endl;
  }
  if(argc>3){
    bombs = validate_numbers((argv[3]));
        // cout<<"here3"<<endl;
  }
  // cout << "Hello World!" << endl;
  mineSweeper myMS;
  cout<<"w = "<<w<<" ,h = "<<h<<" ,bombs = "<<bombs<<endl;
  
  myMS.set_width(w);
  myMS.set_height(h);
  
  Board_t *mb;
  mb = myMS.make_gameBoard(w,h,bombs);
  // cout<<"in main the address returned is "<<(void*)mb<<endl;
  // for (int i = 0; i<;i++){
  //   if (!(i%10)){cout<<endl;}
  //   cout<<(int)mb[i];
      
  // }
  // map <Board_t,SQUARE_t> complexBoard;
  SQUARE_t populatedBoard[myMS.get_width()*myMS.get_height()];
  SQUARE_t * sqtr_ptr;
  sqtr_ptr = populatedBoard;
  myMS.init_board(sqtr_ptr,mb);
  
  myMS.displayBoard(sqtr_ptr);
  
  //main game loop code goes here 
  bool gameOver = false;
  string player_option;
  int option_command;
  int x_coor = 0;
  int y_coor= 0 ;
  // int *xptr;
  // int *yptr;
  // xptr = x_coor;
  // yptr = y_coor;
  while (!gameOver){
    myMS.displayBoard(sqtr_ptr);
    cout << "\nPlayer options:\n1. Reveal space\n2. Flag space\n3. Remove flag";
    cin >> player_option;
    // cout<<"player entered the following..."<<player_option[0]<<endl;
    option_command = handle_player_turn((char)player_option[0],&x_coor,&y_coor);
    if(option_command == 1){
    	cout<<"sending over x = "<<x_coor<<" , y = "<<y_coor<<endl;
    	myMS.open_square(sqtr_ptr,x_coor,y_coor,gameOver);
    }

    if(option_command == 2){
    	myMS.set_flag_square(sqtr_ptr,x_coor,y_coor,true);
    }
	if(option_command == 2){
		myMS.set_flag_square(sqtr_ptr,x_coor,y_coor,false);
	}
	if(option_command == 0){cout<<"\nnot a valid option\n";}

	cout<<"bomb counter == "<<myMS.get_bomb_counter()<<" . and bomb check == "<<myMS.get_bomb_check()<<endl;;
  	if (myMS.get_bomb_check() == myMS.get_bomb_counter()){
  		gameOver = true;
  		cout<<"YOU WIN .......................................\nCONGRATULATIONS!!!!\n";
  	}  
  
  }
  cout<<"\nGAME OVER"<<endl;
  myMS.displayAll(sqtr_ptr);
  
  free(mb);

  return 0;
}

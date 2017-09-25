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

void handle_player_turn(int player_option){
  string x_coor;
  string y_coor;
  if(player_option == 1){
    cout<<"\nenter x coordinate to open.==>";
    cin>>x_coor;
    cout<<"\nenter y coordinate to open.==>";
    cin>>y_coor;
    int clean_x =  validate_numbers(x_coor);
    int clean_y =  validate_numbers(y_coor);
    myMS.open_square(sqtr_ptr,clean_x,clean_y,gameOver);
  }
  else if(player_option == 2){
    out<<"\nenter x coordinate to open.==>";
    cin>>x_coor;
    cout<<"\nenter y coordinate to open.==>";
    cin>>y_coor;
    int clean_x =  validate_numbers(x_coor);
    int clean_y =  validate_numbers(y_coor);
    myMS.flag_square(sqtr_ptr,clean_x,clean_y,gameOver);
  }
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
  int player_option;
  string x_coor;
  string y_coor;
  while (!gameOver){
    myMS.displayBoard(sqtr_ptr);
    cout << "\nPlayer options:\n1. Reveal space\n2. Flag space\n3. Remove flag";
    cin >> player_option;
    handle_player_turn(player_option);
    
  }
  cout<<"\nGAME OVER"<<endl;
  myMS.displayAll(sqtr_ptr);
  
  free(mb);

  return 0;
}

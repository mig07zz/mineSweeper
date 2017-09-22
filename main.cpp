#include <iostream>
#include <cstdlib>
#include "mineSweeper.h"
#include <map>

using namespace std;
 
int main(int argc, char *argv[])
{
  int w = 10;
  int h = 10;
  int bombs = 10;
  if(argc>1){
    w = atoi(argv[1]);
    cout<<"here1"<<endl;
  }
  if(argc>2){
    h = atoi(argv[2]);
        cout<<"here2"<<endl;
  }
  if(argc>3){
    bombs = atoi(argv[3]);
        cout<<"here3"<<endl;
  }
  // cout << "Hello World!" << endl;
  mineSweeper myMS;
  cout<<"w = "<<w<<" ,h = "<<h<<" ,bombs = "<<bombs<<endl;
  
  myMS.set_width(w);
  myMS.set_height(h);
  
  Board_t *mb;
  mb = myMS.make_gameBoard(w,h,bombs);
  cout<<"in main the address returned is "<<(void*)mb<<endl;
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
  
  while (!gameOver){
    
  }
  
  
  free(mb);

  return 0;
}

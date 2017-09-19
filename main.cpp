#include <iostream>
#include <cstdlib>
#include "mineSweeper.h"

using namespace std;
 
int main(void)
{
  cout << "Hello World!" << endl;
  mineSweeper myMS;
  // cout<<myMS.gen_rand_num(1)<<endl;
  
  
  Board_t *mb;
  mb = myMS.make_gameBoard(10,10);
  cout<<"in main the address returned is "<<(void*)mb<<endl;
  for (int i = 0; i<100;i++){
    if (!(i%10)){cout<<endl;}
    cout<<(int)mb[i];
      
  }
  
  free(mb);

  return 0;
}

#include <iostream>
#include "mineSweeper.h"

using namespace std;
 
int main(void)
{
  cout << "Hello World!" << endl;
  mineSweeper myMS;
  // cout<<myMS.gen_rand_num(1)<<endl;
  
  
  myMS.make_gameBoard(10,10);
  return 0;
}

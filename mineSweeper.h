#ifndef MINE_SWEEPER_H
#define MINE_SWEEPER_H

#define MAX_BOARD_SZ 20
#define MIN_BOARD_SZ 2

typedef unsigned char Board;

class mineSweeper{
    struct SQUARE{
        char val;
        bool open;
        bool flagged;
        int neighbor_mines;
        char symbol;
    };
    
  public:
    mineSweeper();
    ~mineSweeper();
    int gen_rand_num(int max);
    Board* make_gameBoard(int width, int height);
    
    //getters
    int get_width();
    int get_height();
    //setters
    void set_width(int width);
    void set_height(int height);
    
  private:
  int board_width;
  int board_height;
    
    
    
};






#endif
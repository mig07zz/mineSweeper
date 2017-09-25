#ifndef MINE_SWEEPER_H
#define MINE_SWEEPER_H

#define MAX_BOARD_SZ 100
#define MIN_BOARD_SZ 2

typedef char Board_t;
typedef struct SQUARE{
    char val ; 
    bool open;
    bool flagged;
    int neighbor_mines;
    char secret;
    int x;
    int y;
}SQUARE_t;


class mineSweeper{

    
  public:
    mineSweeper();
    ~mineSweeper();
    int gen_rand_num(int max);
    Board_t* make_gameBoard(int width, int height, int number_of_mines);
    void init_board(SQUARE_t  *outerBoard,Board_t *innerBoard);
    void displayBoard(SQUARE_t * theBoard);
    void displayAll(SQUARE_t * theBoard);
    void calc_hidden(SQUARE_t * theBoard);
    void open_all_empty_neighbours(SQUARE_t * theBoard, int x, int y);
    
    int coor_to_index(int x, int y);
    
    
    //helper fucntions
    bool has_top_n(int center_x,int center_y);
    bool has_bottom_n(int center_x,int center_y);
    bool has_left_n(int center_x,int center_y);
    bool has_right_n(int center_x,int center_y);
    bool has_topRight_n(int center_x,int center_y);
    bool has_topLeft_n(int center_x,int center_y);
    bool has_bottomRight_n(int center_x,int center_y);
    bool has_bottomLeft_n(int center_x,int center_y);
    // bool neighbor_has_mine(int index);
    void  mineFinder(SQUARE_t* theBoard,int x, int y);
    void open_square(SQUARE_t * theBoard,int x,int y,bool &gameOver);
    
    //getters
    int get_width();
    int get_height();
    //setters
    void set_width(int w);
    void set_height(int h);
    
  private:
  int board_width;
  int board_height;
    
    
    
};






#endif
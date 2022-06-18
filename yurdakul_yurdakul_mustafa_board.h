#ifndef _YURDAKUL_YURDAKUL_MUSTAFA_BOARD_H
#define _YURDAKUL_YURDAKUL_MUSTAFA_BOARD_H
#include <iostream>
using namespace std;

template <class temp>
struct cell
{
    int player;
    temp val;
    cell(){player=0;}
};

template <class temp>
class Board
{
private:
    int rows,cols;
    cell<temp>** data;
public:
    Board(int,int);
    Board(const Board<temp> & rhs);
    ~Board();
    void displayBoard();
    void updateBoardCells(int,temp);
    int getPlayerCellsCount(int);
    int knowTheOwner(int,int);
    bool updateCell(int,int,int,temp);
    void updateAllCells(int,temp);
    bool unclaimOwnership(int,int,int);
    void unclaimOwnerships(int);
};

#include "yurdakul_yurdakul_mustafa_board.cpp"

#endif
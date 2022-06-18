#include "yurdakul_yurdakul_mustafa_board.h"

template <class temp>
Board<temp>::Board(int x, int y)
{
    rows = x;
    cols = y;
    data = new cell<temp> *[x];
    for (int i = 0; i < x; i++)
    {
        data[i] = new cell<temp>[y];
    }
}
template <class temp>
Board<temp>::Board(const Board<temp> &rhs)
{
    rows = rhs.rows;
    cols = rhs.cols;
    data = new cell<temp> *[rhs.rows];
    for (int i = 0; i < rhs.rows; i++)
    {
        data[i] = new cell<temp>[rhs.cols];
    }
    for (int i = 0; i < rhs.rows; i++)
    {
        for (int j = 0; j < rhs.cols; j++)
        {
            data[i][j] = rhs.data[i][j];
        }
    }
}
template <class temp>
Board<temp>::~Board()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] data[i];
    }
    delete[] data;
    data = nullptr;
}
template <class temp>
void Board<temp>::displayBoard()
{
    cout << "Displaying the board: Each cell is shown as tuple (CURRENT OWNER ID, VALUE): " << endl;
    for (int j = 0; j < cols; j++)
    {
        cout << "\t" << j;
    }
    cout << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << i;
        for (int j = 0; j < cols; j++)
        {
            cout << "\t"
                 << "(" << data[i][j].player << "," << data[i][j].val << ")";
        }
        cout << endl;
    }
}
template <class temp>
void Board<temp>::updateBoardCells(int player, temp val)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (data[i][j].player == player)
                data[i][j].val = val;
        }
    }
}
template <class temp>
int Board<temp>::getPlayerCellsCount(int player)
{
    int num = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (knowTheOwner(i,j) == player)
                num++;
        }
    }
    return num;
}
template <class temp>
int Board<temp>::knowTheOwner(int x, int y)
{
    return data[x][y].player;
}
template <class temp>
bool Board<temp>::updateCell(int player, int x, int y, temp val)
{
    if (data[x][y].player == player || data[x][y].player == 0)
    {
        data[x][y].val = val;
        data[x][y].player = player;
        return true;
    }
    else
    {
        return false;
    }
}
template <class temp>
void Board<temp>::updateAllCells(int player, temp val)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (data[i][j].player == player)
                data[i][j].val = val;
        }
    }
}
template <class temp>
bool Board<temp>::unclaimOwnership(int player, int x, int y)
{
    if(data[x][y].player == player)
    {
        data[x][y].player = 0;
        return true;
    }
    else
    {
        return false;
    }
}
template <class temp>
void Board<temp>::unclaimOwnerships(int player)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (data[i][j].player == player)
                data[i][j].player= 0;
        }
    }
}
#ifndef _YURDAKUL_YURDAKUL_MUSTAFA_PLAYER_H
#define _YURDAKUL_YURDAKUL_MUSTAFA_PLAYER_H
#include "yurdakul_yurdakul_mustafa_board.h"

template <class temp>
class Player
{
private:
    int p_num;
    static int static_p_num;
    Board<temp> & shared;
public:
    Player(Board<temp>&);
    bool updateCell(int,int,temp);
    void updateMyCells(temp);
    bool unclaimOwnership(int,int);
    void unclaimOwnerships();
};

#include "yurdakul_yurdakul_mustafa_player.cpp"
#endif
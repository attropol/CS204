#include "yurdakul_yurdakul_mustafa_player.h"

template <class temp>
int Player<temp>::static_p_num = 1;
template <class temp>
Player<temp>::Player(Board<temp>& board)
    :shared(board),p_num(static_p_num)
{
    static_p_num++;
}
template <class temp>
bool Player<temp>::updateCell(int x,int y,temp val)
{
    return shared.updateCell(p_num,x,y,val);
}
template <class temp>
void Player<temp>::updateMyCells(temp val)
{
    shared.updateAllCells(p_num, val);
}
template <class temp>
bool Player<temp>::unclaimOwnership(int x,int y)
{
    return shared.unclaimOwnership(p_num,x,y);
}
template <class temp>
void Player<temp>::unclaimOwnerships()
{
    shared.unclaimOwnerships(p_num);
}
#include "chessboard.h"
//初始化棋盘
chessboard::chessboard()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			grids[i][j].pos.x = i;
			grids[i][j].pos.y = j;
		}
	}
	rand_map();
}

//随机生成地形
void chessboard::rand_map()
{
	//TODO
}

//难度提升
void chessboard::level_up()
{
	difficulty++;
	enemy::level_up();
}
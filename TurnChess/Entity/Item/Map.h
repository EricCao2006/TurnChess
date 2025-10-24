#pragma once
#include "grid.h"
#include <ctime>
//地图，16*9格
class map
{
public:
	grid grids[16][9];
	//初始化棋盘，然后随机生成地形
	map(void){
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
private:
	//随机生成地形
	void rand_map()
	{
		//生成种子
		srand((unsigned int)time(NULL));
	}
};
#pragma once
#include "../Entity/Item/grid.h"
#include "../Entity/Character/enemy.h"
//地图，16*9格
class map
{
public:
	inline static int difficulty = 1; //难度
	static grid grids[16][9];
	static void level_up();
	map();
private:
	static void rand_map();
};

//初始化棋盘
inline map::map()
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
inline void map::rand_map()
{
	//TODO
}

//难度提升
inline void map::level_up()
{
	difficulty++;
	enemy::level_up();
}
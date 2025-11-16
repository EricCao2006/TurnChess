#pragma once
#include "../Entity/Item/grid.h"
#include "../Entity/Character/enemy.h"
#include "../Logic/utils.h"
//棋盘
class chessboard
{
public:
	inline static int difficulty = 1; //难度
	static grid grids[16][9]; //棋盘共16*9格
	static utils::poi_val entities[16][9]; //实体指针与显示字符
	static character* characters[3]; //角色共三个
	static void level_up();
	chessboard();
private:
	static void rand_map();
};


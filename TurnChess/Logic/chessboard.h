#pragma once
#include "../Entity/Item/grid.h"
#include "../Entity/Character/player.h"
#include "../Entity/Character/enemy.h"
#include "../Logic/utils.h"
#define CB chessboard
//棋盘
class chessboard
{
public:
	//棋盘维度：
	static grid* grids[16][9]; //棋盘共16*9格
	static utils::ent_dis entities[16][9]; //实体指针与显示字符
	//棋子维度：
	static player* players[3]; //角色共三个
	static enemy* enemies[100]; //敌人最多一百个
	inline static int level = 1; //关卡等级,角色与怪物属性随等级提升

	static void display();

	static void create_CB();
	static void clear_CB();
	static void load_CB();	
private:
	chessboard() = default;
};


#include "chessboard.h"
#include <iostream>

//初始化空棋盘
void CB::create_CB()
{
	chessboard* cb = new chessboard;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			grids[i][j]->pos.x = i;
			grids[i][j]->pos.y = j;
		}
	}
}

//清空棋盘
void chessboard::clear_CB()
{
	//清空实体二维数组
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 9; j++)
		{
			entities[i][j].ent -> ~entity(); //鸡犬不留
			entities[i][j] = { nullptr,"  " };
		}
	//清空敌人数组
	for (int i = 0; i < 100; i++) enemies[i] = nullptr;
}

//随机生成地形
void CB::load_CB()
{
	//TODO
}

//显示棋盘
void CB::display()
{
	//清空控制台
	system("cls");
	//先显示棋盘
	for (int i=0; i<9;i++)
	{
		for (int j = 0; j < 16; j++)
		{
			std::cout << entities[i][j].dis;
		}							 
		std::cout << std::endl;
	}
}
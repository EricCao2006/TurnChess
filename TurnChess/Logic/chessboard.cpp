#include "chessboard.h"
#include "../Entity/Item/castle.h"
#include "../Entity/Item/barrier.h"
#include "../Entity/Character/enemy.h"
#include "../Entity/Character/player.h"
#include "../Entity/Character/players.h"
#include <iostream>
chessboard* chessboard::CB_ = new chessboard();

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
	//清空角色数组
	for (int i = 0; i < 3; i++) players[i] = nullptr;
}

//随机生成地形
void CB::load_CB()
{
	// 随机放置 10 个障碍物（不重叠）
	int placed = 0;
	while (placed < 10)
	{
		int x = utils::ran_num(0, 15);
		int y = utils::ran_num(0, 8);
		if (entities[x][y].ent == nullptr)
		{
			auto* b = new barrier();
			b->type = BARRIER;
			b->pos = { x, y };
			entities[x][y].ent = b;
			entities[x][y].dis = "##";
			placed++;
		}
	}

	// 随机放置堡垒（选第一个空位），并调用堡垒初始化
	while (true)
	{
		int x = utils::ran_num(0, 15);
		int y = utils::ran_num(0, 8);
		if (entities[x][y].ent == nullptr)
		{
			CA::get_instance()->set_CA(position{ x, y });
			CA::get_instance()->type = CASTLE;
			// 再次确保 entities 填好显示与指针
			entities[x][y].ent = CA::get_instance();
			entities[x][y].dis = CA::get_instance()->display;
			break;
		}
	}

	// 随机放置 3 个玩家（不重叠）
	CB::get_instance()->players[0] = new Saber();
	CB::get_instance()->players[1] = new Archer();
	CB::get_instance()->players[2] = new Healer();
	for (int i = 0; i < 3; ++i)
	{
		while (true)
		{
			int x = utils::ran_num(0, 15);
			int y = utils::ran_num(0, 8);
			if (entities[x][y].ent == nullptr)
			{
				auto* p = CB::get_instance()->players[i];
				p->type = PLAYER;
				p->pos = { x, y };
				players[i] = p;
				entities[x][y].ent = p;
				entities[x][y].dis = p->display;
				break;
			}
		}
	}
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
	//显示角色状态
	for (int i = 0; i < 3; i++)
	{
		auto* p = players[i];
		std::cout << p->name << " 生/攻/防" 
			<< p->health_now << " " 
			<< p->attack_now << " " 
			<< p->defense_now << "    ";
		std::cout << "能量" << p->power;
		std::cout << std::endl;
	}
	
	//显示战技点
	for (int i = 0; i < 3; i++)
	{
		auto* p = players[i];
		std::cout << p->name << " 战技点：" << E_point << std::endl;
	}
	//显示关卡及波次
	std::cout << "关卡进度：" << level << std::endl;
	std::cout << "怪物" << CA::get_instance()->monster_process 
		<< "  Boss" << CA::get_instance()->boss_process
	<< std::endl;
}

//获取当前敌人数量
int chessboard::enemy_num()
{
	int num = 0;
	for (int i = 0; i < 100; i++)
	{
		if (enemies[i] != nullptr)
			num++;
		else break;
	}
	return num;
}

//判断是否所有敌人被击败
bool chessboard::enemies_defeated()
{
	for (int i = 0; i < 100; i++)
	{
		if (enemies[i] != nullptr)
			return false;
	}
	return true;
}
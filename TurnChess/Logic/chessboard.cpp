#include "chessboard.h"
#include "../Entity/Item/castle.h"
#include "../Entity/Item/barrier.h"
#include "../Entity/Character/enemy.h"
#include "../Entity/Character/player.h"
#include "../Entity/Character/players.h"
#include <iostream>
#include <windows.h>

// 定义单例静态成员
chessboard* chessboard::CB_ = new chessboard();

//清空棋盘
void chessboard::clear_CB()
{
	//清空实体二维数组，按类型安全释放（不删除单例堡垒）
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			auto* ent = entities[i][j].ent;
			if (ent != nullptr)
			{
				// 不删除堡垒单例
				if (ent->type != CASTLE)
				{
					delete ent;
				}
				entities[i][j] = { nullptr,"  " };
			}
			else
			{
				entities[i][j] = { nullptr,"  " };
			}
		}
	}
	//清空敌人数组
	for (int i = 0; i < 100; i++) enemies[i] = nullptr;
	//清空角色数组（如果 players 中保存了 new 出来的对象，已在上面删除）
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
				// Ensure display string and name are set
				entities[x][y].dis = p->display;
				if (p->name == "null") {
					// set default name according to concrete type
					if (dynamic_cast<Saber*>(p)) p->name = "Saber";
					else if (dynamic_cast<Archer*>(p)) p->name = "Archer";
					else if (dynamic_cast<Healer*>(p)) p->name = "Healer";
				}
				break;
			}
		}
	}
}

//显示棋盘
void CB::display()
{
	//获取控制台句柄及原始属性，以便恢复
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	WORD originalAttrs = csbi.wAttributes;
	// 提取背景位以便保留背景色
	const WORD bgMask = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
	WORD bg = originalAttrs & bgMask;

	//清空控制台
	system("cls");

	//显示关卡，波次，回合，战技点
	std::cout << "关卡：" << level 
	<< "   Boss：" << CA::get_instance()->boss_process
	<< "   怪物：" << CA::get_instance()->monster_process
	<< "   战技点：" << E_point	<< "/5"
	<< "\n------------------------------------------------\n";

	//显示棋盘: 以 y (0..8) 行为外循环，x (0..15) 列为内循环
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			auto* ent = entities[x][y].ent;
			// 根据实体类型设置前景色，同时保留背景
			if (ent != nullptr)
			{
				if (ent->type == PLAYER)
				{
					SetConsoleTextAttribute(hConsole, bg | FOREGROUND_RED | FOREGROUND_INTENSITY);
				}
				else if (ent->type == ENEMY)
				{
					SetConsoleTextAttribute(hConsole, bg | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				}
				else if (ent->type == BARRIER)
				{
					SetConsoleTextAttribute(hConsole, bg | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}
				else // CASTLE or others
				{
					SetConsoleTextAttribute(hConsole, bg | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				}
			}
			else
			{
				// 空格使用默认浅色前景
				SetConsoleTextAttribute(hConsole, bg | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}

			std::cout << entities[x][y].dis;
		}	 
		std::cout << std::endl;
	}
	// 恢复原始属性，以便后续文本显示正常
	SetConsoleTextAttribute(hConsole, originalAttrs);
	std::cout << "\n------------------------------------------------\n";
	//显示角色状态
	for (int i = 0; i < 3; i++)
	{
		auto* p = players[i];
		std::cout << p->name  
			<< "  生命 " << p->health_now << "/" << static_cast<int>(character::max_health)
			<< "  攻击 " << p->attack_now 
			<< "  防御 " << p->defense_now 
			<< "  能量 " << p->power << "/100";
		std::cout << std::endl;
	}
}

//获取当前敌人数量
int chessboard::enemy_num()
{
	int count = 0;
	for (int i = 0; i < 100; i++)
	{
		if (enemies[i] != nullptr)
		{
			count++;
		}
	}
	return count;
}

//判断是否所有敌人被击败
bool chessboard::enemies_defeated()
{
	for (int i = 0; i < 100; i++)
	{
		if (enemies[i] != nullptr)
		{
			return false;
		}
	}
	return true;
}
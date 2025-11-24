#include "act_list.h"
#include "chessboard.h"
#include "../Entity/Item/castle.h"
act_list* act_list::AL_ = new act_list();

/**
 * @brief 步进:
 * 首项行动并立即刷新,
 * 除首项与死项外依次放入新列表,
 * 首项附加到列表末尾,
 * 新列表替换旧列表
 * @return 是否成功
 */
bool AL::next_step()
{
	acts[0]->act();
	character* new_acts[20];
	int new_i = 0;
	for (int i = 1; i < 20; i++)
	{
		if (acts[i]->health_now > 0)
			new_acts[new_i++] = acts[i];
		else
			acts[i]->~character(); //清除死项
	}
	new_acts[new_i++] = acts[0];
	for (int i = 0; i < new_i; i++)
		acts[i] = new_acts[i];
	for (int i = new_i; i < 20; i++)
		acts[i] = nullptr;	//清除多余项
	CB::get_instance()->display();//刷新棋盘显示
	//如果怪物出完且全部被击败
	if ((CA::get_instance()->is_empty()) 
			&& (CB::get_instance()->enemies_defeated()))
		return true;
	else
	{
		CA::get_instance()->monster_out(); //尝试出怪
		return false;
	}
}

//清空行动列表
void AL::clear_AL()
{
	for (int i = 0; i < 20; i++)
		acts[i] = nullptr;
}

//加载行动列表
void AL::load_AL()
{
	//我一动敌一动
	int enemy_num = CB::get_instance()->enemy_num();
	for (int i = 0; i < enemy_num; i++)
	{
		acts[i*2] = CB::get_instance()->players[i%3];
		acts[i*2+1] = CB::get_instance()->enemies[i];
	}
}
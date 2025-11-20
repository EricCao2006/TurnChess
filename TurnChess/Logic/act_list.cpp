#include "act_list.h"

/**
 * 步进：
 * 首项行动并立即刷新，
 * 除首项与死项外依次放入新列表，
 * 首项附加到列表末尾，
 * 新列表替换旧列表
 */
bool AL::next_step()
{
	acts[0]->act();
	character* new_acts[20];
	int new_i = 0;
	for (int i = 1; i < 20; i++)
		if (acts[i]->health_now > 0)
			new_acts[new_i++] = acts[i];
	new_acts[new_i++] = acts[0];
	for (int i = 0; i < new_i; i++)
		acts[i] = new_acts[i];
	for (int i = new_i; i < 20; i++)
		acts[i] = nullptr;	//清除多余项
	bool completed;
	//TODO:如果堡垒被攻克:
	completed = true;
	//TODO:如果堡垒未被攻克:
	completed = false;
	return completed;
}

//初始化空行动列表
void AL::create_AL()
{
	for (int i = 0; i < 20; i++)
		acts[i] = nullptr;
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
	//TODO:加载行动列表，按照敌我行动比1:1
}
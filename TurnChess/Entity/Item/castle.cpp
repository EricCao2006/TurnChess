#include "castle.h"
#include "../../Logic/utils.h"
#include "../../Logic/chessboard.h"
#include <vector>
#include <string>
castle castle::castle_;

//创建时根据难度调整属性
void CA::set_CA(const position pos)
{
	this->name = "castle";
	this->pos = pos;
	if (monster_total + boss_total < 90)
	{
		this->monster_total = 4 + CB::get_instance()->level;
		this->boss_total = 1 + (CB::get_instance()->level / 3);
	}
	//放置到棋盘上
	CB::get_instance()->entities[pos.x][pos.y].ent = this;
	CB::get_instance()->entities[pos.x][pos.y].dis = this->display;
	monster_out(); //第0波出怪
}

/**
 * @brief 3*3随机出怪，避开障碍物和已有单位
 * @return 出怪是否成功
 */
inline void castle::monster_out()
{
	// 计算 3x3 区域内可放置的位置（不越界且无实体）
	std::vector<position> free_positions;
	for (int dx = -1; dx <= 1; ++dx)
	{
		for (int dy = -1; dy <= 1; ++dy)
		{
			int nx = pos.x + dx;
			int ny = pos.y + dy;
			// 棋盘尺寸 16 x 9
			if (nx < 0 || ny < 0 || nx >= 16 || ny >= 9) continue;
			// 避开堡垒自身所在格（可根据需要允许）
			// if (dx == 0 && dy == 0) continue;
			auto* ent = CB::get_instance()->entities[nx][ny].ent;
			// 如果该格为空或仅为格子展示（无实体），则认为可放置
			if (ent == nullptr)
			{
				free_positions.push_back(position{ nx, ny });
			}
		}
	}

	// 没有可放置位置，直接返回
	if (free_positions.empty()) return;

	// 计算剩余待出的怪与首领数量
	int rem_mon = monster_total - monster_already;
	int rem_boss = boss_total - boss_already;

	// 如果都已出完，直接返回
	if (rem_mon <= 0 && rem_boss <= 0) return;

	// 按“未出怪比例”选择生成怪或首领
	bool spawn_boss = false;
	if (rem_mon > 0 && rem_boss > 0)
	{
		int pick = utils::ran_num(1, rem_mon + rem_boss);
		if (pick > rem_mon) spawn_boss = true;
	}
	else if (rem_boss > 0)
	{
		spawn_boss = true;
	}
	else
	{
		spawn_boss = false;
	}

	// 随机选一个空位（3x3 等概率）
	int idx = utils::ran_num(0, static_cast<int>(free_positions.size() - 1));
	position chosen = free_positions[idx];

	// 生成实体并放置到棋盘
	if (spawn_boss)
	{
		auto* b = new boss();
		b->type = ENEMY;
		b->pos = chosen;
		// 将实体指针放到棋盘对应格
		CB::get_instance()->entities[chosen.x][chosen.y].ent = b;
		++boss_already;
		// 将首领加入敌人列表
		while (true)
		{
			int i = 0;
			if (CB::get_instance()->enemies[i] == nullptr)
			{
				CB::get_instance()->enemies[i] = b;
				break;
			}
			++i;
		}
	}
	else
	{
		auto* m = new monster();
		m->type = ENEMY;
		m->pos = chosen;
		CB::get_instance()->entities[chosen.x][chosen.y].ent = m;
		++monster_already;
		// 将小怪加入敌人列表
		while (true)
		{
			int i = 0;
			if (CB::get_instance()->enemies[i] == nullptr)
			{
				CB::get_instance()->enemies[i] = m;
				break;
			}
			++i;
		}
	}

	// 更新显示的进度字符串
	monster_process = std::to_string(monster_already) + "/" + std::to_string(monster_total);
	boss_process = std::to_string(boss_already) + "/" + std::to_string(boss_total);
}

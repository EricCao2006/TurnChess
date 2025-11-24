#include "players.h"
#include "../../Logic/chessboard.h"
#include "../../Logic/utils.h"
#include <algorithm>
#include <cmath>

Saber::Saber()
{
	name = "Saber ";//多加一个空格对齐
    display = "Sa"; 
}

Archer::Archer()
{
    name = "Archer";
    display = "Ar";
}

Healer::Healer()
{
    name = "Healer";
    display = "He";
}

// 应用伤害（只对 character 生效）
static void apply_damage(entity* e, int dmg)
{
	if (e == nullptr) return;
	if (e->type != ENEMY && e->type != PLAYER) return;
	auto* ch = static_cast<character*>(e);
	ch->attacked(dmg);
}

// 对单个盟友恢复生命
static void heal_target(player* p, int heal_amount)
{
	if (p == nullptr) return;
	p->health_now = std::min(static_cast<int>(p->max_health), p->health_now + heal_amount);
}

/* Saber 技能 */
// 3x3 近战范围攻击，倍率 2
void Saber::A_skill()
{
	const int mult = 2;
	int base = this->attack_now;
	for (int dx = -1; dx <= 1; ++dx)
	{
		for (int dy = -1; dy <= 1; ++dy)
		{
			int nx = pos.x + dx;
			int ny = pos.y + dy;
			if (nx < 0 || ny < 0 || nx >= 16 || ny >= 9) continue;
			auto* ent = CB::get_instance()->entities[nx][ny].ent;
			if (ent != nullptr && ent->type == ENEMY)
				apply_damage(ent, base * mult);
		}
	}
}

// 5x5 近战范围攻击，倍率 4
void Saber::E_skill()
{
	const int mult = 4;
	int base = this->attack_now;
	for (int dx = -2; dx <= 2; ++dx)
	{
		for (int dy = -2; dy <= 2; ++dy)
		{
			int nx = pos.x + dx;
			int ny = pos.y + dy;
			if (nx < 0 || ny < 0 || nx >= 16 || ny >= 9) continue;
			auto* ent = CB::get_instance()->entities[nx][ny].ent;
			if (ent != nullptr && ent->type == ENEMY)
				apply_damage(ent, base * mult);
		}
	}
}

// 全屏攻击，倍率 6
void Saber::Q_skill()
{
	const int mult = 6;
	int base = this->attack_now;
	for (int x = 0; x < 16; ++x)
	{
		for (int y = 0; y < 9; ++y)
		{
			auto* ent = CB::get_instance()->entities[x][y].ent;
			if (ent != nullptr && ent->type == ENEMY)
				apply_damage(ent, base * mult);
		}
	}
}

/* Archer 技能 */
// 远程单体攻击，倍率 5：选最近的可达敌人（按曼哈顿）并攻击
void Archer::A_skill()
{
	const int mult = 5;
	int base = this->attack_now;
	int best_d = INT_MAX;
	entity* best = nullptr;
	for (int x = 0; x < 16; ++x)
	{
		for (int y = 0; y < 9; ++y)
		{
			auto* ent = CB::get_instance()->entities[x][y].ent;
			if (ent != nullptr && ent->type == ENEMY)
			{
				int d = std::abs(x - pos.x) + std::abs(y - pos.y);
				if (d < best_d)
				{
					best_d = d;
					best = ent;
				}
			}
		}
	}
	if (best != nullptr) apply_damage(best, base * mult);
}

// 3x3 远程范围攻击，倍率 10（以自身中心的 3x3）
void Archer::E_skill()
{
	const int mult = 10;
	int base = this->attack_now;
	for (int dx = -1; dx <= 1; ++dx)
	{
		for (int dy = -1; dy <= 1; ++dy)
		{
			int nx = pos.x + dx;
			int ny = pos.y + dy;
			if (nx < 0 || ny < 0 || nx >= 16 || ny >= 9) continue;
			auto* ent = CB::get_instance()->entities[nx][ny].ent;
			if (ent != nullptr && ent->type == ENEMY)
				apply_damage(ent, base * mult);
		}
	}
}

// 全屏攻击，倍率 4；对首领（boss）伤害翻倍
void Archer::Q_skill()
{
	const int mult = 4;
	int base = this->attack_now;
	for (int x = 0; x < 16; ++x)
	{
		for (int y = 0; y < 9; ++y)
		{
			auto* ent = CB::get_instance()->entities[x][y].ent;
			if (ent != nullptr && ent->type == ENEMY)
			{
				// 检测是否为 boss：尝试 dynamic_cast（若不是多态则回退按基类处理）
				auto* maybe_boss = dynamic_cast<boss*>(static_cast<character*>(ent));
				int dmg = base * mult;
				if (maybe_boss != nullptr) dmg *= 2;
				apply_damage(ent, dmg);
			}
		}
	}
}

/* Healer 技能 */
// 单体治疗：回复 50% 最大生命
void Healer::A_skill()
{
	// 选择优先受伤最严重的盟友（包括自己）
	player* target = nullptr;
	double worst_ratio = 1.1; // 越小越危险
	for (int i = 0; i < 3; ++i)
	{
		auto* p = CB::get_instance()->players[i];
		if (p == nullptr) continue;
		if (p->health_now <= 0) continue; // 复活交给 Q 技能
		double ratio = static_cast<double>(p->health_now) / p->max_health;
		if (ratio < worst_ratio)
		{
			worst_ratio = ratio;
			target = p;
		}
	}
	if (target == nullptr) return;
	int heal_amount = static_cast<int>(target->max_health * 0.5);
	heal_target(target, heal_amount);
}

// 全体治疗并提升本关全体 50% 生命上限
void Healer::E_skill()
{
	// 提升全体生命上限（静态 max_health），并按新上限补满生命
	character::max_health *= 1.5;
	for (int i = 0; i < 3; ++i)
	{
		auto* p = CB::get_instance()->players[i];
		if (p == nullptr) continue;
		p->health_now = static_cast<int>(p->max_health);
	}
	// 也为棋盘上的所有玩家（如有其他引用）做同步
}

// 全体治疗与复活；本关内提高全体 20% 攻击力
void Healer::Q_skill()
{
	// 先复活并全回血
	for (int i = 0; i < 3; ++i)
	{
		auto* p = CB::get_instance()->players[i];
		if (p == nullptr) continue;
		if (p->health_now <= 0)
		{
			// 简单复活：将生命设为满
			p->health_now = static_cast<int>(p->max_health);
		}
		else
		{
			p->health_now = static_cast<int>(p->max_health);
		}
	}
	// 提升全体攻击力 20%
	character::norm_attack = static_cast<int>(std::ceil(character::norm_attack * 1.2));
}
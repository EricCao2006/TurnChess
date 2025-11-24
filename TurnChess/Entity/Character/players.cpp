#include "players.h"
#include "../../Logic/chessboard.h"
#include "../../Logic/utils.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
#include <array>
#include <vector>

Saber::Saber()
{
	name = "Saber ";//多加一个空格对齐
    display = "Sa";
	defense = base_defense * 2; // 剑士防御力较高
	max_health = static_cast<int>(base_health);
	health_now = max_health;
}

Archer::Archer()
{
    name = "Archer";
    display = "Ar";
	attack = base_attack * 2; // 弓箭手攻击力较高
	max_health = static_cast<int>(base_health);
	health_now = max_health;
}

Healer::Healer()
{
    name = "Healer";
    display = "He";
	max_health = static_cast<int>(base_health) * 2;	// 治疗师生命值较高
	health_now = max_health;
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
	p->health_now = std::min(static_cast<int>(p->base_health), p->health_now + heal_amount);
}

// 靠近敌人移动一步
static bool move_toward(player* self)
{
    if (self == nullptr) return false;
    constexpr int W = 16;
    constexpr int H = 9;
    auto* cb = CB::get_instance();

    // BFS to find nearest enemy
    bool vis[W][H] = { false };
    std::pair<int,int> prev[W][H];
    for (int i = 0; i < W; ++i)
        for (int j = 0; j < H; ++j)
            prev[i][j] = { -1, -1 };

    std::queue<std::pair<int,int>> q;
    q.push({ self->pos.x, self->pos.y });
    vis[self->pos.x][self->pos.y] = true;

    std::pair<int,int> found = { -1, -1 };
    const std::array<std::pair<int,int>,8> dirs = { std::pair{1,0}, std::pair{-1,0}, std::pair{0,1}, std::pair{0,-1}, std::pair{1,1}, std::pair{1,-1}, std::pair{-1,1}, std::pair{-1,-1} };

    while (!q.empty() && found.first == -1)
    {
        auto [cx, cy] = q.front(); q.pop();
        for (auto [dx, dy] : dirs)
        {
            int nx = cx + dx;
            int ny = cy + dy;
            if (nx < 0 || ny < 0 || nx >= W || ny >= H) continue;
            if (vis[nx][ny]) continue;

            auto* ent = cb->entities[nx][ny].ent;
            // can traverse only empty cells; if it's an enemy, we've found target
            if (ent != nullptr && ent->type != ENEMY) continue;

            vis[nx][ny] = true;
            prev[nx][ny] = { cx, cy };

            if (ent != nullptr && ent->type == ENEMY)
            {
                found = { nx, ny };
                break;
            }
            q.push({ nx, ny });
        }
    }

    if (found.first == -1) return false;

    // trace back to step
    std::pair<int,int> cur = found;
    std::pair<int,int> step = found;
    while (prev[cur.first][cur.second].first != -1)
    {
        step = cur;
        cur = prev[cur.first][cur.second];
        if (cur.first == self->pos.x && cur.second == self->pos.y) break;
    }

    if (step.first == self->pos.x && step.second == self->pos.y) return false;

    // move self to step if it's empty
    if (cb->entities[step.first][step.second].ent != nullptr) return false;

    if (cb->entities[self->pos.x][self->pos.y].ent == self)
        cb->entities[self->pos.x][self->pos.y].ent = nullptr;
    cb->entities[self->pos.x][self->pos.y].dis = "  ";

    cb->entities[step.first][step.second].ent = self;
    cb->entities[step.first][step.second].dis = self->display;

    self->pos.x = step.first;
    self->pos.y = step.second;

    return true;
}

// 远离最近敌人一步；返回是否移动
static bool move_away(player* self)
{
    if (self == nullptr) return false;
    constexpr int W = 16;
    constexpr int H = 9;
    auto* cb = CB::get_instance();

    // gather enemy positions
    std::vector<std::pair<int,int>> enemy_positions;
    for (int i = 0; i < 100; ++i)
    {
        auto* e = cb->enemies[i];
        if (e != nullptr)
            enemy_positions.emplace_back(e->pos.x, e->pos.y);
    }
    if (enemy_positions.empty()) return false;

    const std::array<std::pair<int,int>,8> dirs = { std::pair{1,0}, std::pair{-1,0}, std::pair{0,1}, std::pair{0,-1}, std::pair{1,1}, std::pair{1,-1}, std::pair{-1,1}, std::pair{-1,-1} };
    int best_score = -1;
    std::pair<int,int> best_cell = { self->pos.x, self->pos.y };

    auto min_dist_to_enemy = [&](int x, int y){
        int md = INT_MAX;
        for (auto &ep : enemy_positions)
        {
            int d = std::abs(ep.first - x) + std::abs(ep.second - y);
            if (d < md) md = d;
        }
        return md;
    };

    int cur_score = min_dist_to_enemy(self->pos.x, self->pos.y);
    best_score = cur_score;

    for (auto [dx, dy] : dirs)
    {
        int nx = self->pos.x + dx;
        int ny = self->pos.y + dy;
        if (nx < 0 || ny < 0 || nx >= W || ny >= H) continue;
        auto* ent = cb->entities[nx][ny].ent;
        if (ent != nullptr) continue; // only consider empty cells
        int score = min_dist_to_enemy(nx, ny);
        if (score > best_score)
        {
            best_score = score;
            best_cell = { nx, ny };
        }
    }

    if (best_cell.first == self->pos.x && best_cell.second == self->pos.y) return false;

    // perform move
    if (cb->entities[self->pos.x][self->pos.y].ent == self)
        cb->entities[self->pos.x][self->pos.y].ent = nullptr;
    cb->entities[self->pos.x][self->pos.y].dis = "  ";

    cb->entities[best_cell.first][best_cell.second].ent = self;
    cb->entities[best_cell.first][best_cell.second].dis = self->display;

    self->pos.x = best_cell.first;
    self->pos.y = best_cell.second;

    return true;
}

/* Saber 技能 */
// 3x3 近战范围攻击，倍率 2
void Saber::A_skill()
{
	move_toward(this);
	const int mult = 2;
	int base = this->attack;
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
	move_toward(this);
	const int mult = 4;
	int base = this->attack;
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
	move_toward(this);
	const int mult = 6;
	int base = this->attack;
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
	move_away(this);
	const int mult = 5;
	int base = this->attack;
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
	move_away(this);
	const int mult = 10;
	int base = this->attack;
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
	move_away(this);
	const int mult = 4;
	int base = this->attack;
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
	move_away(this);
	// 选择优先受伤最严重的盟友（包括自己）
	player* target = nullptr;
	double worst_ratio = 1.1; // 越小越危险
	for (int i = 0; i < 3; ++i)
	{
		auto* p = CB::get_instance()->players[i];
		if (p == nullptr) continue;
		if (p->health_now <= 0) continue; // 复活交给 Q 技能
		double ratio = static_cast<double>(p->health_now) / p->base_health;
		if (ratio < worst_ratio)
		{
			worst_ratio = ratio;
			target = p;
		}
	}
	if (target == nullptr) return;
	int heal_amount = static_cast<int>(target->base_health * 0.5);
	heal_target(target, heal_amount);
}

// 全体治疗并提升本关全体 50% 生命上限
void Healer::E_skill()
{
	move_away(this);
	// 提升我方全体生命上限（静态 max_health），并按新上限补满生命
	for (int i = 0; i < 3; ++i)
	{
		auto* p = CB::get_instance()->players[i];
		if (p == nullptr) continue;
		p->max_health *= 1.5;
		p->health_now = p->max_health;
	}
	// 也为棋盘上的所有玩家（如有其他引用）做同步
}

// 全体治疗与复活；本关内提高全体 20% 攻击力
void Healer::Q_skill()
{
	move_away(this);
	// 先复活并全回血
	for (int i = 0; i < 3; ++i)
	{
		auto* p = CB::get_instance()->players[i];
		if (p == nullptr) continue;
		if (p->health_now <= 0)
		{
			// 简单复活：将生命设为满
			p->health_now = static_cast<int>(p->base_health);
		}
		else
		{
			p->health_now = static_cast<int>(p->base_health);
		}
	}
	// 提升全体攻击力 20%
	character::base_attack = static_cast<int>(std::ceil(character::base_attack * 1.2));
}


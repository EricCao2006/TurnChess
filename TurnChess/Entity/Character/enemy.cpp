#include "enemy.h"
#include "../../Logic/utils.h"
#include "../../Logic/chessboard.h"
#include <queue>
#include <utility>
#include <array>

// 初始化小怪
monster::monster()
{
	max_health = static_cast<int>(base_health);
	health_now = max_health;
	attack = base_attack;
	defense = base_defense;
	display = "Mo";
	type = ENEMY;
}

// 初始化首领
boss::boss()
{
	max_health = 5 * static_cast<int>(base_health);
	health_now = max_health;
	attack = 5 * base_attack;
	defense = 2 * base_defense;
	display = "Bo";
	type = ENEMY;
}

// 小怪攻击
void monster::act()
{
	int x= pos.x; int y = pos.y;
	position* around = utils::around_pos(pos);
	//攻击周围顺时针找到的第一个角色
	for (int i = 0; i < 8; i++)
	{
		x = around[i].x; y = around[i].y;
		//确保坐标合法
		if (x >= 0 && y >= 0 && x <= 15 && y <= 8)
		{
			auto* target = CB::get_instance()->entities[x][y].ent;
			if (target != nullptr )
			{
				if (target->type == PLAYER)
				{
					static_cast<character*>(target)->attacked(attack);
					return;	//攻击后结束行动
				}
			}
		}
		around++; //继续旋转寻人
	}
	//如果没有，则向直角距离最近的角色移动一步，绕开障碍物
	constexpr int W = 16;
	constexpr int H = 9;
	bool vis[W][H] = { false };
	std::pair<int, int> prev[W][H];
	for (int i = 0; i < W; ++i)
		for (int j = 0; j < H; ++j)
			prev[i][j] = { -1, -1 };

	std::queue<std::pair<int, int>> q;
	q.push({ pos.x, pos.y });
	vis[pos.x][pos.y] = true;

	std::pair<int, int> found = { -1, -1 };
	const std::array<std::pair<int, int>, 4> dirs = { std::pair{1,0}, std::pair{-1,0}, std::pair{0,1}, std::pair{0,-1} };

	while (!q.empty() && found.first == -1)
	{
		auto [cx, cy] = q.front(); q.pop();
		for (auto [dx, dy] : dirs)
		{
			int nx = cx + dx;
			int ny = cy + dy;
			if (nx < 0 || ny < 0 || nx >= W || ny >= H) continue;
			if (vis[nx][ny]) continue;

			auto* ent = CB::get_instance()->entities[nx][ny].ent;
			// 如果该格有实体且不是玩家，则视为障碍不能通过
			if (ent != nullptr && ent->type != PLAYER) continue;

			vis[nx][ny] = true;
			prev[nx][ny] = { cx, cy };

			// 如果找到玩家，记录并退出搜索（BFS 保证最短路径）
			if (ent != nullptr && ent->type == PLAYER)
			{
				found = { nx, ny };
				break;
			}
			// 空格或玩家格（如果玩家没有被当作障碍继续推进），继续扩展
			q.push({ nx, ny });
		}
	}

	// 未找到可达玩家则不移动
	if (found.first == -1) return;

	// 从 found 回溯到起点，找到起点之后的第一步
	std::pair<int, int> cur = found;
	std::pair<int, int> step = found;
	while (prev[cur.first][cur.second].first != -1)
	{
		step = cur;
		cur = prev[cur.first][cur.second];
		if (cur.first == pos.x && cur.second == pos.y) break;
	}
	// step 是从起点出发的第一步坐标（如果已经在邻近格，step 可能等于 found）

	// 如果第一步是当前位置（不移动），则返回
	if (step.first == pos.x && step.second == pos.y) return;

	// 更新棋盘上的实体指针（将当前位置设为空、目标格指针设为自己）
	auto* cb = CB::get_instance();
	// 防护：确保旧格确实指向自己再清空（以免误清）
	if (cb->entities[pos.x][pos.y].ent == this)
		cb->entities[pos.x][pos.y].ent = nullptr;
	// 如果目标格是玩家则不覆盖玩家（通常不会发生，因为我们只移动到空格或靠近玩家）
	if (cb->entities[step.first][step.second].ent == nullptr)
		cb->entities[step.first][step.second].ent = this;
	// 删除原位置
	cb->entities[pos.x][pos.y].ent = nullptr;
	cb->entities[pos.x][pos.y].dis = "  ";
	// 更新自身坐标
	pos.x = step.first;
	pos.y = step.second;
	//放置到棋盘上
	cb->entities[pos.x][pos.y].ent = this;
	cb->entities[pos.x][pos.y].dis = display;

}

// 首领攻击
void boss::act()
{
	//全屏攻击
	for (int i = 0; i < 3; i++)
	{
		auto* target = CB::get_instance()->players[i];
		target->attacked(attack);
	}
}
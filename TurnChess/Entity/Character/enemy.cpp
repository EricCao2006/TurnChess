#include "enemy.h"
#include "../../Logic/utils.h"
#include "../../Logic/chessboard.h"
// 初始化小怪属性
monster::monster()
{
	health_now = static_cast<int>(max_health);
	attack_now = norm_attack;
	defense_now = norm_defense;
}

// 初始化首领属性
boss::boss()
{
	health_now = 10 * static_cast<int>(max_health);
	attack_now = 5 * norm_attack;
	defense_now = 10 * norm_defense;
}

/**
 * @brief 敌人属性随难度提升
 *
 * 生乘1.2倍，攻防提1点
 */
void enemy::level_up()
{
	max_health *= 1.2;
	norm_attack += 1;
	norm_defense += 1;
}

// 小怪攻击
void monster::attack()
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
			auto* target = chessboard::entities[x][y].poi;
			if (target != nullptr )
			{
				if (target->type == PLAYER)
				{
					static_cast<character*>(target)->attacked(attack_now);
					break;
				}
			}
		}
		around++;
	}
	//如果没有，那么计算直角距离最近的角色，并靠近一格(上场角色共三个)
	int dis = 25; //对角线不超过25
	int tmp_dis = 0;
	character* cha = nullptr;
	character* tmp_cha = chessboard::characters[0];
	for (size_t i = 0; i < 3; i++)
	{
		tmp_dis = tmp_cha->pos.x + tmp_cha->pos.y - x - y; 
		if (dis < 0) tmp_dis = -tmp_dis;
		if (tmp_dis < dis)
		{
			dis = tmp_dis;
			cha = tmp_cha;
		}
		tmp_cha++;
	}
	
	
}
#include "character.h"
#include <algorithm>
/**
	 * @brief 伤害计算：
	 *
	 * 防御乘区为1/(1+防御力%)，
	 *
	 * 最低伤害为1点，最高伤害致死;
	 *
	 * 直接修改当前生命值
	 */
void character::attacked(const int attack_value)
{
	const double defense = 1.0 / (1.0 + this->defense);
	int damage = static_cast<int>(attack_value * defense);
	damage = std::clamp(damage, 1, health_now);//定界
	health_now -= damage;
}

/**
 * @brief 属性随难度提升
 *
 * 生乘1.2倍，攻提1点，防提1点
 */
void character::level_up()
{
	base_health *= 1.2;
	base_attack += 1;
	base_defense += 1;
}
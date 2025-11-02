#pragma once
#include "../character.h"
//敌人
class enemy : public character
{
protected:
	//敌人的基础属性
	inline static double max_health = 10.0;
	inline static int norm_attack = 1;
	inline static int norm_defense = 1;
	//敌人的当前属性
	int health_now = 0;
	int attack_now = 0;
	int defense_now = 0;
public:
	static void level_up();
};

//小怪
class monster : public enemy
{
public:
	monster();
};

//首领，生防为小怪10倍，攻为5倍
class boss : public enemy
{
public:
	boss();
};

// 初始化敌人属性
inline monster::monster()
{
	health_now = static_cast<int>(max_health);
	attack_now = norm_attack;
	defense_now = norm_defense;
}
inline boss::boss()
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
inline void enemy::level_up()
{
	max_health *= 1.2;
	norm_attack += 1;
	norm_defense += 1;
}

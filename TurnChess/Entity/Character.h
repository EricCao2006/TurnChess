#pragma once
#include "entity.h"
//角色
class character : public entity
{
public:
	// 基础属性
	inline static double max_health = 10.0; // 生命值上限
	inline static int norm_attack = 1; // 常态攻击力
	inline static int norm_defense = 1; // 常态防御力
	// 当前属性
	int health_now = 0; // 当前生命值
	int attack_now = 0; // 当前攻击力
	int defense_now = 0; // 当前防御力
	//行动
	virtual void act() = 0;
	//受到攻击
	void attacked(const int attack_value);
	static void level_up();
};

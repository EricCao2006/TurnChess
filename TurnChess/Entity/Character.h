#pragma once
#include "entity.h"
//角色
class character : public entity
{
public:
	// 基础属性
	inline static double base_health = 10.0; // 基准生命值
	inline static int base_attack = 1; // 基准攻击力
	inline static int base_defense = 1; // 基准防御力
	// 当前属性
	int max_health = 10; // 最大生命值
	int health_now = 10; // 当前生命值
	int attack = 1; // 攻击力
	int defense = 2; // 防御力
	//行动
	virtual void act() = 0;
	//受到攻击
	void attacked(const int attack_value);
	static void level_up();
};

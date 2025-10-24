#pragma once
#include "entity.h"
#include "Character/status.h"
//角色
class character : public entity
{
public:
	// 基础属性
	int max_health = 10; // 生命值上限
	int norm_attack = 1; // 常态攻击力
	int norm_defense = 1; // 常态防御力
	// 当前属性
	int health_now = 10; // 当前生命值
	int attack_now = 1; // 当前攻击力
	int defense_now = 1; // 当前防御力
	status statuses[5]; // 当前状态
};
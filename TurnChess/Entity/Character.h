#pragma once
#include "entity.h"
#include "Character/status.h"
//角色
class character : public entity
{
public:
	int health_basic = 10; // 常态生命值
	int attack_basic = 1; // 常态攻击力
	int defense_basic = 1; // 常态防御力
	int health_now = 10; // 当前生命值
	int attack_now = 1; // 当前攻击力
	int defense_now = 1; // 当前防御力
	status status_now[10]; // 当前状态
};
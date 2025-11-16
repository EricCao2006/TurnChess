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
	virtual void attack() = 0;
};

//小怪
class monster : public enemy
{
public:
	monster();
	void attack() override;
};

//首领，生防为小怪10倍，攻为5倍
class boss : public enemy
{
public:
	boss();
	void attack() override;
};

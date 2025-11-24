#pragma once
#include "../character.h"
//敌人
class enemy : public character {};

//小怪
class monster : public enemy
{
public:
	monster();
	void act() override;
};

//首领，生攻为小怪5倍，防为2倍
class boss : public enemy
{
public:
	boss();
	void act() override;
};

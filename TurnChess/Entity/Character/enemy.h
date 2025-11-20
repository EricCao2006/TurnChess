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

//首领，生防为小怪10倍，攻为5倍
class boss : public enemy
{
public:
	boss();
	void act() override;
};

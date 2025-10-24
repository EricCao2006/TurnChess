#pragma once
#include "../character.h"
#include "skill.h"
#include "status.h"
//玩家角色
class player : public character
{
public:
	int level = 1; //等级
	int exp = 0;   //经验值
	//行动
	void act(skill)
	{
		//TODO
	}
private:
	skill normal_skill; //普攻
	skill combat_skill; //战技
	skill ultimate_skill; //大招
};
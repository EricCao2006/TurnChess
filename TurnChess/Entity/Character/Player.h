#pragma once
#include "../character.h"
#include "skill.h"
//玩家角色
class player : public character
{
public:
	string under_show = "角色名 等级1 经验0/100 生/攻/防0/0/0 无状态";
	string display = "Pl"; //显示字符
	//行动
	void act(skill); //TODO
	//攻破堡垒
	void break_castle();
private:
	int level = 1; //等级
	int exp = 0;   //经验值
	skill normal_skill; //普攻
	skill combat_skill; //战技
	skill ultimate_skill; //大招
};
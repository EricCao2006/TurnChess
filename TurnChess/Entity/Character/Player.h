#pragma once
#include "../character.h"
//玩家角色
class player : public character
{
public:
	string under_show = "角色名 等级1 经验0/100 生/攻/防0/0/0 无状态";
	string display = "Pl"; //默认显示字符
	int player_id = 0; //角色ID

	void act() override; //行动
	void break_castle(); //攻破堡垒
	player();
private:
	virtual void A_skill() = 0; //普攻
	virtual void E_skill() = 0; //战技
	virtual void Q_skill() = 0; //大招
};


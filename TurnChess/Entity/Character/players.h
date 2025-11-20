#pragma once
#include "player.h"

//剑士
class Saber : public player
{ 
public:
	string display = "Sa";
	void A_skill() override; //普攻
	void E_skill() override; //战技
	void Q_skill() override; //大招
};

//弓箭手
class Archer : public player
{
	string display = "Ar";
	void A_skill() override; //普攻
	void E_skill() override; //战技
	void Q_skill() override; //大招
};

//治疗
class Healer : public player
{
	string display = "He";
	void A_skill() override; //普攻
	void E_skill() override; //战技
	void Q_skill() override; //大招
};
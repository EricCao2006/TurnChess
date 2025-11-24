#pragma once
#include "player.h"

//剑士
class Saber : public player
{ 
public:
	Saber();
	void A_skill() override; //普攻
	void E_skill() override; //战技
	void Q_skill() override; //大招
};

//弓箭手
class Archer : public player
{
public:
	Archer();
	void A_skill() override; //普攻
	void E_skill() override; //战技
	void Q_skill() override; //大招
};

//治疗师
class Healer : public player
{
public:
	Healer();
	void A_skill() override; //普攻
	void E_skill() override; //战技
	void Q_skill() override; //大招
};
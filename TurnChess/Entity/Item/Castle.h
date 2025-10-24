#pragma once
#include "../item.h"
//堡垒(攻克后变为宝箱)
class castle : public item
{
public:
	bool is_broken = false;	//是否被攻克
	int provide_exp = 10; //提供经验值
	int monster_total = 5; //总出怪数
	int monster_already = 0; //已出怪数
	int boss_total = 0; //总出boss数
	int boss_already = 0; //已出boss数
	string display = displays[0]; //显示字符，默认未攻克
private:
	string displays[2] = { "!!","$$" }; //0为未攻克，1为已攻克
};
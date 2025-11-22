#pragma once
#include "../item.h"
#include "../Character/player.h"
/**
 * @brief 堡垒
 * 难度++，出怪++，出boss++1/3
 */
class castle : public item
{
public:
	string monster_process = "0/4"; //出怪进度
	string boss_process = "0/1"; //出boss进度
	string display = displays[0]; //显示字符，默认未攻克
	castle(position);//生成堡垒和第0波出怪
	bool monster_out(); //出怪
private:
	bool is_broken = false;	//是否被攻克
	int monster_total = 4; //总出怪数
	int monster_already = 0; //已出怪数
	int boss_total = 1; //总出boss数
	int boss_already = 0; //已出boss数
	string displays[2] = { "!!","$$" }; //0为未攻克，1为已攻克
};

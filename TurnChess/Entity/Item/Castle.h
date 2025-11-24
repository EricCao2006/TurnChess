#pragma once
#include "../item.h"
#include "../Character/player.h"
#define CA castle

/**
 * @brief 堡垒
 * 难度++，出怪++，出boss++1/3
 */
class castle : public item
{
public:
	static castle* get_instance() { return &castle_; }//单例获取
	string monster_process = "0/4"; //出怪进度
	string boss_process = "0/1"; //出boss进度
	string display = "!!"; 
	void set_CA(position);//移位和第0波出怪
	void monster_out(); //出怪
	bool is_empty() //怪物是否出完
	{
		if ((monster_already == monster_total)&& (boss_already == boss_total) )
			return true;
		else return false;
	}
private:
	int monster_total = 4; //总出怪数
	int monster_already = 0; //已出怪数
	int boss_total = 1; //总出boss数
	int boss_already = 0; //已出boss数
	castle() = default;//禁止外部实例化 
	static castle castle_;//单例
};

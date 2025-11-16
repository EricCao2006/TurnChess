#pragma once
#include "../item.h"
/*
 * 方格
 * 用于简化伤害判定
 */
class grid : public item
{
public:
	position pos = {.x=0,.y=0};//再声明一遍
	bool is_bleed = false; //是否为流血格
	bool to_p_or_e = true; //对玩家流血1，对敌人流血0
	string display = displays[1];//显示字符，默认普通格
private:
	string displays[2] = { "__","  " };//0为流血格，1为普通格
};

#include "castle.h"
#include "../../Logic/chessboard.h"

//创建时根据难度调整属性
inline castle::castle(const position pos)
{
	this->name = "castle";
	this->pos = pos;
	provide_exp = 10 * chessboard::difficulty;
	this->monster_total = 4 + chessboard::difficulty;
	this->boss_total = 1 + (chessboard::difficulty / 3);
	//第0波出怪
	//TODO
}

/**
 * @brief 3*3等概率随机出怪，
 *
 * 避开障碍物和已有单位
 * @return 出怪是否成功
 */
inline bool castle::monster_out()
{
	//检测能否出怪
	bool used[8];
	//生成随机数1~8
	utils::ran_num(1, 8);
	//TODO
}

inline void player::break_castle()
{
	exp += castle::provide_exp;
}
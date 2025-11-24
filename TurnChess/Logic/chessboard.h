#pragma once
#include "../Entity/Character/player.h"
#include "../Entity/Character/enemy.h"
#include "../Logic/utils.h"
#define CB chessboard
//棋盘&全局状类(单例)
class chessboard
{
public:
	//棋盘共16*9格
	utils::ent_dis entities[16][9]; //实体指针与显示字符
	player* players[3] = { nullptr }; //角色共三个
	enemy* enemies[100] = { nullptr }; //敌人最多一百个
	int level = 1; //关卡等级,角色与怪物属性随等级提升
	int E_point = 3; //战技点，每关初始3点，上线5点
	
	void display();
	void clear_CB();
	void load_CB();
	static CB* get_instance(){return CB_;} 
	int enemy_num(); //获取当前敌人数量
	bool enemies_defeated(); //判断是否所有敌人被击败
private:
	CB() = default;//禁止外部实例化
	static CB* CB_;//单例
};


#pragma once
#include "../Entity/character.h"
#define AL act_list
//行动顺序列表
class act_list
{
public:
	static constexpr int MAX_ACTS = 200;
	character* acts[MAX_ACTS];
	int turns = 0; //记录回合数
	bool next_step();
	void clear_AL();
	void load_AL();
	static act_list* get_instance();
private:
	act_list();
	~act_list();
	static act_list* AL_;//单例
};
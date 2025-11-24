#pragma once
#include "../Entity/character.h"
#define AL act_list
//行动顺序列表
class act_list
{
public:
	character* acts[200];
	bool next_step();
	void clear_AL();
	void load_AL();
	static act_list* get_instance() { return AL_; }
private:
	act_list() = default;//禁止外部实例化
	static act_list* AL_;//单例
};
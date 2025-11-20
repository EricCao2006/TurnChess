#pragma once
#include "../Entity/character.h"
#define AL act_list
//行动顺序列表，单例
class act_list
{
public:
	static character* acts[200];

	static bool next_step();

	static void create_AL();
	static void clear_AL();
	static void load_AL();

private:
	act_list() = default;
};
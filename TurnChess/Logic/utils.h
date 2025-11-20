#pragma once
#include "../Entity/entity.h"

//工具集
class utils
{
public:

	//实体及其显示字符
	struct ent_dis
	{
		entity* ent = nullptr;
		string dis = "  ";
	};

	static position* around_pos(const position& pos);
	static int ran_num(const int lower, const int upper);

};
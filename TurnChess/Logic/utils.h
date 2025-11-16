#pragma once
#include "../Entity/entity.h"

//工具集
class utils
{
public:

	//键值对，键为实体指针
	struct poi_val
	{
		entity* poi;
		string value;
	};

	static position* around_pos(const position& pos);
	static int ran_num(const int lower, const int upper);

};
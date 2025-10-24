#pragma once
#include <string>
using std::string;
//横纵坐标
struct position
{
	int x = 0;
	int y = 0;
};
//实体
class entity
{
public:
	string name = "null";
	int id = 0;
	position pos = {.x=0,.y=0};
};
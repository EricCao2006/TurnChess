#pragma once
#include <string>
using std::string;

//横纵坐标
struct position
{
	int x = 0;
	int y = 0;
};

//实体类型
enum entity_type
{ PLAYER,ENEMY,BARRIER,CASTLE };
//实体
class entity
{
public:
	string name = "null";
	entity_type type = PLAYER;
	string display = "  "; //此处相当于char display[3] = "  ";
	position pos = {.x=0,.y=0};
};
#include "utils.h"
#include <random>

// 线程安全、均匀的随机整数 [lower, upper]
int utils::ran_num(const int lower, const int upper)
{
	static std::mt19937_64 rng((unsigned)std::random_device{}());
	std::uniform_int_distribution<int> dist(lower, upper);
	return dist(rng);
}

//顺时针环绕坐标数组，从0点钟方向开始
position* utils::around_pos(const position& pos)
{
	static position around[8];
	around[0] = {.x=pos.x,.y=pos.y+1};
	around[1] = {.x=pos.x+1,.y=pos.y+1};
	around[2] = {.x=pos.x+1,.y=pos.y};
	around[3] = {.x=pos.x+1,.y=pos.y-1};
	around[4] = {.x=pos.x,.y=pos.y-1};
	around[5] = {.x=pos.x-1,.y=pos.y-1};
	around[6] = {.x=pos.x-1,.y=pos.y};
	around[7] = {.x=pos.x-1,.y=pos.y+1};
	return around;
}
#include "utils.h"
#include <random>
#include <ctime>
/**
 * @brief 随机数生成，每次都以当前时间戳重置种子
 * @param lower 下限（包含）
 * @param upper 上限（包含）
 */
static int ran_num(const int lower, const int upper)
{
	//获取时间戳
	const int time = static_cast<int>(std::time(nullptr));
	//设置随机数种子
	std::default_random_engine e(time);
	//生成随机数
	std::uniform_int_distribution<int> u(lower, upper);
	//返回随机数
	return u(e);
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
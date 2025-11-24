#include "utils.h"
#include <random>

// 返回围绕某点的 8 个相邻格（顺时针：上, 右上, 右, 右下, 下, 左下, 左, 左上）
// 使用静态数组返回指针，调用者无需也不应 delete（项目中多处未释放）。
position* utils::around_pos(const position& pos)
{
	static position around[8];
	// 上
	around[0] = { pos.x,     pos.y - 1 };
	// 右上
	around[1] = { pos.x + 1, pos.y - 1 };
	// 右
	around[2] = { pos.x + 1, pos.y     };
	// 右下
	around[3] = { pos.x + 1, pos.y + 1 };
	// 下
	around[4] = { pos.x,     pos.y + 1 };
	// 左下
	around[5] = { pos.x - 1, pos.y + 1 };
	// 左
	around[6] = { pos.x - 1, pos.y     };
	// 左上
	around[7] = { pos.x - 1, pos.y - 1 };

	return around;
}

// 实现随机数生成函数
int utils::ran_num(const int lower, const int upper)
{
	if (lower > upper) return lower;
	static std::mt19937 rng((unsigned)std::random_device{}());
	std::uniform_int_distribution<int> dist(lower, upper);
	return dist(rng);
}
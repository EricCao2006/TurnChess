#pragma once
#include <algorithm>
#include <random>
#include <ctime>

//运行逻辑
class logic
{
public:
	/** 
	 * @brief 防御乘区为1/(1+防御力%)，
	 * 
	 *        最低伤害为1点，最高伤害致死;
	 *
	 *        直接修改当前生命值
	 */
	static void attacked(int & health_now, const int attack_now, const int defense_now)
	{
		const double defense = 100.0 / (100.0 + defense_now);
		int damage = static_cast<int>(attack_now * defense);
		damage = std::clamp(damage, 1, health_now);
		health_now -= damage;
	}

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
};
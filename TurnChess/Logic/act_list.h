#pragma once
#include "../Entity/character.h"
//行动顺序列表，单例
class act_list
{
public:
	character acts[20];
	//初始化行动顺序
	act_list()
	{
		//TODO
	}
	/**
	 * 推进一步：
	 * 首项与死项外依次放入新列表，
	 * 首项附加到列表末尾，
	 * 新列表替换旧列表
	 */
	void next_step()
	{
		character new_acts[20];
		int new_i = 0;
		for (int i = 1; i < 20; i++)
			if (acts[i].health_now > 0)
				new_acts[new_i++] = acts[i];
		new_acts[new_i++] = acts[0];
		for (int i = 0; i < new_i; i++)
			acts[i] = new_acts[i];
		for (int i = new_i; i < 20; i++)
			acts[i] = character();	//清除多余项
	}
};
#include "act_list.h"
#include "chessboard.h"
#include "../Entity/Item/castle.h"
#include <algorithm>
act_list* act_list::AL_ = nullptr;

act_list::act_list()
{
	for (int i = 0; i < MAX_ACTS; ++i)
		acts[i] = nullptr;
}

act_list::~act_list()
{
	// act_list 不负责删除 character 实例（除非明确 ownership），仅清空指针
	for (int i = 0; i < MAX_ACTS; ++i)
		acts[i] = nullptr;
}

act_list* act_list::get_instance()
{
	if (!AL_) AL_ = new act_list();
	return AL_;
}

/**
 * @brief 步进:
 * 首项行动并立即刷新,
 * 除首项与死项外依次放入新列表,
 * 首项附加到列表末尾,
 * 新列表替换旧列表
 * @return 是否成功
 */
bool AL::next_step()
{
    // 若首项为空，尝试加载行动列表；仍无数据则安全返回
    if (!acts[0])
    {
        load_AL();
        if (!acts[0])
            return false;
    }

    acts[0]->act();

    character* new_acts[MAX_ACTS] = { nullptr };
    int new_i = 0;
    for (int i = 1; i < MAX_ACTS; ++i)
    {
        if (acts[i] && acts[i]->health_now > 0)
        {
            new_acts[new_i++] = acts[i];
        }
        else if (acts[i])
        {
            // 不调用显式析构；如果 act_list 拥有对象生命周期，应改为 delete acts[i];
            acts[i] = nullptr;
        }
    }

    if (acts[0])
        new_acts[new_i++] = acts[0];

    // 复制回 acts，并清空后续槽
    for (int i = 0; i < new_i && i < MAX_ACTS; ++i)
        acts[i] = new_acts[i];
    for (int i = new_i; i < MAX_ACTS; ++i)
        acts[i] = nullptr;

    CB::get_instance()->display();
    turns++;//回合数+1
    if ((CA::get_instance()->is_empty())
        && (CB::get_instance()->enemies_defeated()))
        return true;
    else
    {
        CA::get_instance()->monster_out();
        return false;
    }

}

void AL::clear_AL()
{
    for (int i = 0; i < MAX_ACTS; ++i)
        acts[i] = nullptr;
	turns = 0;//回合数归零
}

void AL::load_AL()
{
    // 先清空槽，确保一致性
    for (int i = 0; i < MAX_ACTS; ++i) acts[i] = nullptr;

    int enemy_num = CB::get_instance()->enemy_num();
    const int player_count = 3;
    int rounds = std::max(enemy_num, player_count);
    int idx = 0;
    for (int i = 0; i < rounds && idx < MAX_ACTS; ++i)
    {
        // always try to put player i (wrap or direct?) - use players[i] where i < player_count
        if (i < player_count)
        {
            auto* p = CB::get_instance()->players[i];
            if (p != nullptr && idx < MAX_ACTS) acts[idx++] = p;
        }
        // then put enemy i if exists
        if (i < enemy_num)
        {
            auto* e = CB::get_instance()->enemies[i];
            if (e != nullptr && idx < MAX_ACTS) acts[idx++] = e;
        }
    }
	turns = 0;//回合数归零
}
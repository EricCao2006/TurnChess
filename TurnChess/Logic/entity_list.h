#pragma once
#include "../Entity/entity.h"

//实体指针表以链表形式存储
struct node
{
	entity* ptr = nullptr;
	int id = 0;
	node* next = nullptr;
};

//实体链表头
extern node head;

//实体追加
inline void add_ent(entity* ent)
{
	if (ent == nullptr) return;
	auto new_node = new node;
	//头为空
	if (head.next == nullptr)
	{
		head.next = new_node;
		new_node->ptr = ent;
		new_node->id = 1;
		ent->id = 1;
	}
	//头不为空
	else
	{
		auto p = &head;
		while (p->next != nullptr)
			p = p->next;
		p->next = new_node;
		new_node->ptr = ent;
		new_node->id = (p->id) + 1;
		ent->id = new_node->id;
	}
}

//实体删除
inline void del_ent(const int id)
{
	auto p = &head;
	while (p->next != nullptr && p->next->id != id)
		p = p->next;
	//未找到
	if (p->next == nullptr) return;
	//找到，删除
	auto to_del = p->next;
	p->next = to_del->next;
	// 删除实体对象（如果链表负责实体生命周期），否则删除这行
	if (to_del->ptr != nullptr)
		delete to_del->ptr;
	delete to_del;
	// 更新后续节点的 id 并同步到实体
	auto cur = p->next;
	while (cur != nullptr)
	{
		cur->id -= 1;
		if (cur->ptr != nullptr)
			cur->ptr->id = cur->id;
		cur = cur->next;
	}
}
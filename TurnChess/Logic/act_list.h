#pragma once
#include "../Entity/character.h"
//�ж�˳���б�����
class act_list
{
public:
	character acts[20];
	//��ʼ���ж�˳��
	act_list()
	{
		//TODO
	}
	/**
	 * �ƽ�һ����
	 * ���������������η������б�
	 * ����ӵ��б�ĩβ��
	 * ���б��滻���б�
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
			acts[i] = character();	//���������
	}
};
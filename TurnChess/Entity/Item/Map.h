#pragma once
#include "grid.h"
#include <ctime>
//��ͼ��16*9��
class map
{
public:
	grid grids[16][9];
	//��ʼ�����̣�Ȼ��������ɵ���
	map(void){
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				grids[i][j].pos.x = i;
				grids[i][j].pos.y = j;
			}
		}
		rand_map();
	}
private:
	//������ɵ���
	void rand_map()
	{
		//��������
		srand((unsigned int)time(NULL));
	}
};
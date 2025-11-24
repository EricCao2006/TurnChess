//主程序
#include "Runtime.h"

int main()
{
    //初始化单例
	CB* cb = CB::get_instance();//棋盘
	AL* al = AL::get_instance();//行动列表
	CA* ca = CA::get_instance();//堡垒

	//旗帜变量
	bool completed = false;
	bool lose = false;

	//主循环
	while (true)
	{
		lose = false;
		cb->level = 1; //重置难度
		//一局
		while (true){
			completed = false;
			//一关内
			while (completed==false)
			{
				completed = al->next_step();
				if (lose) break;
				//else continue;
			}
			system("cls");//清屏
			//每关小结:下一关/重新开始/结束游戏
			if (lose)
			{
				cout << "游戏结束！" << std::endl;
				break;
			}
			else 
			{
				cout << "关卡" << (cb->level) << "胜利！" << std::endl
					<< "1.下一关 2.结算" << std::endl;
				char choice;
				cin >> choice;
				if (choice == '1') 
				{
					cout << "正在加载中...";
					cb->level++;
					character::level_up();
					cb->clear_CB();
					cb->load_CB();
					al->clear_AL();
					al->load_AL();
					continue;
				}
				else break; 
			}
		}
		cout << "本次您到达了" << cb->level << "关！" << std::endl
			 << "1.重新开始 2.结束游戏" << std::endl;
		char choice;
		cin >> choice;
		if (choice == '1') 
		{
			cout << "正在加载中...";
			continue;
		}
		else
		{
			cout << "感谢您的游玩！"; 
			return 0;
		}
	}
}
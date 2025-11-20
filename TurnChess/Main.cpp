//主程序

#include "Runtime.h"

int main()
{
    //创建容器
	CB::create_CB();
	AL::create_AL();

	//旗帜变量
	bool completed = false;
	bool lose = false;
	bool to_exit = false;

	//主循环
	while (true)
	{
		lose = false;
		CB::level = 1; //重置难度
		//一局
		while (true){
			completed = false;
			//一关内
			while (completed==false)
			{
				completed = AL::next_step();
				if (lose) break;
				//else continue;
			}

			//TODO:每关小结:下一关/重新开始/结束游戏
			if (lose)
			{
				cout << "游戏结束！" << std::endl;
				break;
			}
			else 
			{
				cout << "关卡" << (CB::level) << "胜利！" << std::endl
					<< "1.下一关 2.结算" << std::endl;
				char choice;
				cin >> choice;
				if (choice == '1') 
				{
					cout << "正在加载中...";
					CB::level++;
					character::level_up();
					CB::clear_CB();
					CB::load_CB();
					AL::clear_AL();
					AL::load_AL();
					continue;
				}
				else break; 
			}
		}
		cout << "本次您到达了" << CB::level << "关！" << std::endl
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
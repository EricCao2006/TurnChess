#include "player.h"
#include "../../Logic/chessboard.h"
#include <iostream>
/* 
 * 战技点上限为5，战技-1（需有），普攻+1，大招不变
 * 大招消耗能量100，普攻+10，战技+30
 */
void player::act()
{
	char choice;
	std::cout << "[INFO] " << name << "行动，";
	while (true)
	{
		std::cout << "请选择技能：A-普攻 E-战技 Q-大招" << std::endl;
		std::cin >> choice;
		if (choice == 'A' || choice == 'a')
		{
			A_skill();
			power += 10;
			power = std::min(power, 100);
			if (CB::get_instance()->E_point < 5)
				CB::get_instance()->E_point += 1;
			break;
		}
		else if (choice == 'E' || choice == 'e')
		{
			if (CB::get_instance()->E_point > 0)
			{
				E_skill();
				CB::get_instance()->E_point -= 1;
				power += 30;
				power = std::min(power, 100);
				break;
			}
			else
			{
				std::cout << "[WARN] 战技点不足！" << std::endl;
			}
		}
		else if (choice == 'Q' || choice == 'q')
		{
			if (power >= 100)
			{
				Q_skill();
				power -= 100;
				break;
			}
			else
			{
				std::cout << "[WARN] 能量不足！" << std::endl;
			}
		}
		else
		{
			std::cout << "[WARN] 输入无效，请重新选择！" << std::endl;
		}
	}
}

player::player()
{
	health_now = static_cast<int>(base_health);
	attack = base_attack;
	defense = base_defense;
}

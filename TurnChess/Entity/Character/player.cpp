#include "player.h"
#include <iostream>

void player::act()
{
	char choice;
	std::cout << name << "行动，按A/E/Q释放普攻、战技或大招";
	std::cin >> choice;

	switch (choice) {
	case 'E':
		E_skill();
		break;
	case 'Q':
		Q_skill();
		break;
	case 'A'://默认为普攻
	default:
		A_skill();
		break;
	}
}

player::player()
{
	health_now = static_cast<int>(max_health);
	attack_now = norm_attack;
	defense_now = norm_defense;
}

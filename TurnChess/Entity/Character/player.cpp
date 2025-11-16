#include "player.h"
#include <iostream>

void player::act()
{
	char choice;
	std::cout << name << "行动，按A/E/Q释放普攻、战技或大招";
	std::cin >> choice;

	switch (choice) {
	case 'E':
		//TODO
		break;
	case 'Q':
		//TODO
		break;
	case 'A'://默认为普攻
	default:
		//TODO
		break;
	}
}

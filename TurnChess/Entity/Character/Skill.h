#pragma once
//技能范围，0~3分别为对单、范围、直线、全屏
enum scopes {to_one, area, straight, full_screen};

//技能
class skill
{
public:
	int scope = to_one; //技能范围
	/**
	 * 技能类型，0为攻击，1为治疗
	 * 攻击倍率基于攻击力，治疗倍率基于生命值
	 */
	bool attack_or_treat =true; 
	float magnification = 1.00f; //技能倍率
};
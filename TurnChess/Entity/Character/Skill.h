#pragma once
//���ܷ�Χ��0~3�ֱ�Ϊ�Ե�����Χ��ֱ�ߡ�ȫ��
enum scopes {to_one, area, straight, full_screen};

//����
class skill
{
public:
	int scope = to_one; //���ܷ�Χ
	/**
	 * �������ͣ�0Ϊ������1Ϊ����
	 * �������ʻ��ڹ����������Ʊ��ʻ�������ֵ
	 */
	bool attack_or_treat =true; 
	float magnification = 1.00f; //���ܱ���
};
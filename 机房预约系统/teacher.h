#pragma once
#include"identity.h"

class Teacher :public Identity
{
public:
	//Ĭ�Ϲ��캯��
	Teacher();

	//�вι��캯��
	Teacher(int empId, string name, string pwd);

	//�˵�����
	void operMenu();

	//��ʾ����ԤԼ
	void showAllOrder();

	//���ԤԼ
	void validOrder();

	//ְ����
	int m_empId;
};
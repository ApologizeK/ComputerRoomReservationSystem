#pragma once
#include"identity.h"

class Teacher :public Identity
{
public:
	//默认构造函数
	Teacher();

	//有参构造函数
	Teacher(int empId, string name, string pwd);

	//菜单界面
	void operMenu();

	//显示所有预约
	void showAllOrder();

	//审核预约
	void validOrder();

	//职工号
	int m_empId;
};
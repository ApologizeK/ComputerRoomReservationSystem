#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include<vector>

//身份抽象基类
class Identity
{
public:
	//操作函数 纯虚函数
	virtual void operMenu() = 0;

	//用户名
	string m_name;
	string m_pwd;
};
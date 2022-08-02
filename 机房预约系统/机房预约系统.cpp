#include<iostream>
using namespace std;
#include "identity.h"
#include "globalFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"

//进入管理员子菜单界面
void managerMenu(Identity*& manager)
{
	while (true)
	{
		//调用管理员子类菜单
		manager->operMenu();

		//将父类指针转为子类指针 调用子类里的其他接口
		Manager* man = (Manager*)manager;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//添加账号
			man->addPerson();
		}
		else if (select == 2)
		{
			//查看账号
			man->showPerson();
		}
		else if (select == 3)
		{
			//查看机房
			man->showComputer();
		}
		else if (select == 4)
		{
			//清空预约
			man->cleanFile();
		}
		else
		{
			delete manager;//清空堆区空间
			cout << "注销成功！" << endl;
			return;
		}
	}
}

//进入学生子菜单
void studentMenu(Identity*& student)
{
	while (true)
	{
		student->operMenu();
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//申请预约
			stu->applyOrder();
		}
		else if (select == 2)
		{
			//查看我的预约
			stu->showMyOrder();
		}
		else if (select == 3)
		{
			//查看所有预约
			stu->showAllOrder();
		}
		else if (select == 4)
		{
			//取消预约
			stu->cancelOrder();
		}
		else
		{
			delete student;
			cout << "注销成功！" << endl;
			//system("pause");
			//system("cls");
			return;
		}
	}
}

//进入教师子菜单
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//查看所有预约
			tea->showAllOrder();

		}
		else if (select == 2)
		{
			//审核预约

			tea->validOrder();
		}
		else
		{
			delete teacher;
			cout << "注销成功！" << endl;
			return;
		}
	}
}

void loginIn(string fileName, int type)
{
	//父类指针用于指向子类 形成多态
	Identity* person = NULL;

	ifstream ifs(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	int id;
	string name;
	string pwd;

	if (type == 1)
	{
		//学生
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入你的职工号：" << endl;
		cin >> id;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;
	if (type == 1)
	{
		//学生
		int fid;
		string fname;
		string fpwd;
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fname == name && fpwd == pwd)
			{
				cout << "学生验证登录成功！" << endl;
				person = new Student(id, name, pwd);
				system("pause");
				system("cls");
				//进入学生子菜单
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//老师
		int fid;
		string fname;
		string fpwd;
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fname == name && fpwd == pwd)
			{
				cout << "老师验证登录成功！" << endl;
				person = new Teacher(id, name, pwd);
				system("pause");
				system("cls");
				//进入老师子菜单
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员
		string fname;
		string fpwd;
		while (ifs >> fname && ifs >> fpwd)
		{
			if (fname == name && fpwd == pwd)
			{
				cout << "管理员验证登录成功！" << endl;
				person = new Manager(name, pwd);
				system("pause");
				system("cls");
				//进入管理员子菜单
				managerMenu(person);
				return;
			}
		}
	}
	cout << "验证登陆失败！" << endl;
}

int main()
{
	int select = 0;
	while (true)
	{
		cout << "====================欢迎使用传智播客机房预约系统============================" << endl;
		cout << endl << "请输入您的身份：" << endl;
		cout << "\t\t--------------------------------------" << endl;
		cout << "\t\t|                                    |" << endl;
		cout << "\t\t|             1.学生代表             |" << endl;
		cout << "\t\t|                                    |" << endl;
		cout << "\t\t|             2.老    师             |" << endl;
		cout << "\t\t|                                    |" << endl;
		cout << "\t\t|             3.管 理 员             |" << endl;
		cout << "\t\t|                                    |" << endl;
		cout << "\t\t|             0.退    出             |" << endl;
		cout << "\t\t|                                    |" << endl;
		cout << "\t\t--------------------------------------" << endl;
		cout << "请输入您的选择：" << endl;
		cin >> select;
		switch (select)
		{
		case 1://学生登录
			loginIn(STUDENT_FILE, 1);
			break;
		case 2://老师登录
			loginIn(TEACHER_FILE, 2);
			break;
		case 3://管理员登录
			loginIn(ADMIN_FILE, 3);
			break;
		case 0://退出
			cout << "欢迎下次使用！" << endl;
			return 0;
			break;
		default:
			cout << "输入有误，请重新输入！" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
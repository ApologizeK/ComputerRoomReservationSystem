#include "student.h"
#include"globalFile.h"

//默认构造
Student::Student()
{

}

//有参构造
Student::Student(int id, string name, string pwd)
{
	this->m_id = id;
	this->m_name = name;
	this->m_pwd = pwd;
	ifstream ifs(COMPUTERROOM_FILE, ios::in);
	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		this->vCom.push_back(c);
	}
	ifs.close();

}

//菜单界面
void Student::operMenu()
{
	cout << "欢迎学生代表" << this->m_name << "登录！" << endl;
	cout << "\t\t--------------------------------------" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             1.申请预约             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             2.查看我的预约         |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             3.查看所有预约         |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             4.取消预约             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             0.注销登录             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t--------------------------------------" << endl;
	cout << "请输入您的选择：" << endl;
}

//申请预约
void Student::applyOrder()
{
	cout << "机房开放的时间为周一到周五！" << endl;
	cout << "请输入申请预约的时间（1.周一 2.周二 3.周三 4.周四 5.周五）：" << endl;
	int date = 0;//日期
	int interval = 0;//时间段
	int room = 0;//机房编号
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	cout << "请输入申请预约的时间段（1.上午 2.下午）:" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	cout << "请选择机房（）：" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << "号机房的容量为：" << vCom[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	cout << "预约成功！审核中！" << endl;

	ofstream ofs(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_id << " ";
	ofs << "stuName:" << this->m_name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();
	system("pause");
	system("cls");
}

//查看自身预约
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++)
	{
		//string 利用.c_str()转const char* 再利用atoi()转int
		if (this->m_id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			cout << "预约的日期：周" << of.m_orderData[i]["date"];
			cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 学号：" << of.m_orderData[i]["stuId"];
			cout << " 姓名：" << of.m_orderData[i]["stuName"];
			cout << " 机房号：" << of.m_orderData[i]["roomId"];
			string status = " 状态:";
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "预约失败";
			}
			else if (of.m_orderData[i]["status"] == "0")
			{
				status += "预约取消";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}

//查看所有预约
void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++)
	{
		cout << i + 1 << "、";
		//string 利用.c_str()转const char* 再利用atoi()转int
		cout << "预约的日期：周" << of.m_orderData[i]["date"];
		cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 机房号：" << of.m_orderData[i]["roomId"];
		string status = " 状态:";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败";
		}
		else if (of.m_orderData[i]["status"] == "0")
		{
			status += "预约取消";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

//取消预约
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或预约成功的记录可以取消，请输入取消的记录：" << endl;
	vector<int>v;
	int index = 1;
	for (int i = 0; i < of.m_size; i++)
	{
		if (this->m_id == atoi(of.m_orderData[i]["stuId"].c_str()))
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、";
				cout << "预约的日期：周" << of.m_orderData[i]["date"];
				cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 机房号：" << of.m_orderData[i]["roomId"];
				string status = " 状态:";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				else if (of.m_orderData[i]["status"] == "-1")
				{
					status += "预约失败";
				}
				else if (of.m_orderData[i]["status"] == "0")
				{
					status += "预约取消";
				}
				cout << status << endl;

			}
		}
	}

	cout << "请输入取消的记录，0代表返回" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入！" << endl;
	}

	system("pause");
	system("cls");
}
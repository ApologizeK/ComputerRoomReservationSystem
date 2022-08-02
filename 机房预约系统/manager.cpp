#include"manager.h"
#include"globalFile.h"
#include<algorithm>

//构造函数
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string pwd)
{
	//初始化管理员信息
	this->m_name = name;
	this->m_pwd = pwd;
	//初始化容器
	this->initVector();
}

//菜单界面
void Manager::operMenu()
{
	cout << "欢迎管理员" << this->m_name << "登录！" << endl;
	cout << "\t\t--------------------------------------" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             1.添加账号             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             2.查看账号             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             3.查看机房             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             4.清空预约             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             0.注销登录             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t--------------------------------------" << endl;
	cout << "请输入您的选择：" << endl;
}

//添加账号
void Manager::addPerson()
{
	cout << "请输入添加账号类型(1.学生 2.老师)：" << endl;
	string filename;
	string tip;
	string errortip;
	ofstream ofs;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		filename = STUDENT_FILE;
		tip = "请输入学号：";
		errortip = "学号重复，请重新输入！";
	}
	else
	{
		filename = TEACHER_FILE;
		tip = "请输入职工编号：";
		errortip = "职工号重复，请重新输入！";
	}

	ofs.open(filename, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret)
			cout << errortip << endl;
		else
			break;
	}
	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入密码：" << endl;
	cin >> pwd;
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功！" << endl;
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();
}


void printStudent(Student& s)
{
	cout << "学号：" << s.m_id << "\t姓名：" << s.m_name << "\t密码：" << s.m_pwd << endl;
}

void printTeacher(Teacher& t)
{
	cout << "职工号：" << t.m_empId << "\t姓名：" << t.m_name << "\t密码：" << t.m_pwd << endl;
}
//查看账号
void Manager::showPerson()
{
	cout << "请选择查看的内容（1.查看学生 2.查看老师）：" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "所有的学生信息如下：" << endl;
		for_each(this->vStu.begin(), this->vStu.end(), printStudent);
	}
	else if (select == 2)
	{
		cout << "所有的教师信息如下：" << endl;
		for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

//查看机房信息
void Manager::showComputer()
{
	cout << "机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = this->vCom.begin(); it != this->vCom.end(); it++)
	{
		cout << "机房编号：" << (*it).m_ComId << "\t机房最大容量：" << (*it).m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}

//初始化容器
void Manager::initVector()
{
	this->vStu.clear();
	this->vTea.clear();
	ifstream ifs(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << STUDENT_FILE << "文件读取失败！" << endl;
		ifs.close();
		return;
	}
	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_pwd)
	{
		this->vStu.push_back(s);
	}
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << TEACHER_FILE << "文件读取失败！" << endl;
		ifs.close();
		return;
	}
	Teacher t;
	while (ifs >> t.m_empId && ifs >> t.m_name && ifs >> t.m_pwd)
	{
		this->vTea.push_back(t);
	}
	ifs.close();
	//cout << this->vStu.size() << this->vTea.size() << endl;

	ifs.open(COMPUTERROOM_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << COMPUTERROOM_FILE << "文件读取失败！" << endl;
		ifs.close();
		return;
	}
	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		this->vCom.push_back(c);
	}
	ifs.close();
}

//检测重复
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = this->vStu.begin(); it != this->vStu.end(); it++)
		{
			if ((*it).m_id == id)
				return true;
		}
	}
	else if (type == 2)
	{
		for (vector<Teacher>::iterator it = this->vTea.begin(); it != this->vTea.end(); it++)
		{
			if ((*it).m_empId == id)
				return true;
		}
	}

	return false;
}
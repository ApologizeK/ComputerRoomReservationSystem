#include"manager.h"
#include"globalFile.h"
#include<algorithm>

//���캯��
Manager::Manager()
{

}

//�вι���
Manager::Manager(string name, string pwd)
{
	//��ʼ������Ա��Ϣ
	this->m_name = name;
	this->m_pwd = pwd;
	//��ʼ������
	this->initVector();
}

//�˵�����
void Manager::operMenu()
{
	cout << "��ӭ����Ա" << this->m_name << "��¼��" << endl;
	cout << "\t\t--------------------------------------" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             1.����˺�             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             2.�鿴�˺�             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             3.�鿴����             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             4.���ԤԼ             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             0.ע����¼             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t--------------------------------------" << endl;
	cout << "����������ѡ��" << endl;
}

//����˺�
void Manager::addPerson()
{
	cout << "����������˺�����(1.ѧ�� 2.��ʦ)��" << endl;
	string filename;
	string tip;
	string errortip;
	ofstream ofs;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		filename = STUDENT_FILE;
		tip = "������ѧ�ţ�";
		errortip = "ѧ���ظ������������룡";
	}
	else
	{
		filename = TEACHER_FILE;
		tip = "������ְ����ţ�";
		errortip = "ְ�����ظ������������룡";
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
	cout << "������������" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ���" << endl;
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();
}


void printStudent(Student& s)
{
	cout << "ѧ�ţ�" << s.m_id << "\t������" << s.m_name << "\t���룺" << s.m_pwd << endl;
}

void printTeacher(Teacher& t)
{
	cout << "ְ���ţ�" << t.m_empId << "\t������" << t.m_name << "\t���룺" << t.m_pwd << endl;
}
//�鿴�˺�
void Manager::showPerson()
{
	cout << "��ѡ��鿴�����ݣ�1.�鿴ѧ�� 2.�鿴��ʦ����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "���е�ѧ����Ϣ���£�" << endl;
		for_each(this->vStu.begin(), this->vStu.end(), printStudent);
	}
	else if (select == 2)
	{
		cout << "���еĽ�ʦ��Ϣ���£�" << endl;
		for_each(this->vTea.begin(), this->vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

//�鿴������Ϣ
void Manager::showComputer()
{
	cout << "������Ϣ���£�" << endl;
	for (vector<ComputerRoom>::iterator it = this->vCom.begin(); it != this->vCom.end(); it++)
	{
		cout << "������ţ�" << (*it).m_ComId << "\t�������������" << (*it).m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}

//��ʼ������
void Manager::initVector()
{
	this->vStu.clear();
	this->vTea.clear();
	ifstream ifs(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << STUDENT_FILE << "�ļ���ȡʧ�ܣ�" << endl;
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
		cout << TEACHER_FILE << "�ļ���ȡʧ�ܣ�" << endl;
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
		cout << COMPUTERROOM_FILE << "�ļ���ȡʧ�ܣ�" << endl;
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

//����ظ�
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
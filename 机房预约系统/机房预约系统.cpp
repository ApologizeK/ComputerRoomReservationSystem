#include<iostream>
using namespace std;
#include "identity.h"
#include "globalFile.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"

//�������Ա�Ӳ˵�����
void managerMenu(Identity*& manager)
{
	while (true)
	{
		//���ù���Ա����˵�
		manager->operMenu();

		//������ָ��תΪ����ָ�� ����������������ӿ�
		Manager* man = (Manager*)manager;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//����˺�
			man->addPerson();
		}
		else if (select == 2)
		{
			//�鿴�˺�
			man->showPerson();
		}
		else if (select == 3)
		{
			//�鿴����
			man->showComputer();
		}
		else if (select == 4)
		{
			//���ԤԼ
			man->cleanFile();
		}
		else
		{
			delete manager;//��ն����ռ�
			cout << "ע���ɹ���" << endl;
			return;
		}
	}
}

//����ѧ���Ӳ˵�
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
			//����ԤԼ
			stu->applyOrder();
		}
		else if (select == 2)
		{
			//�鿴�ҵ�ԤԼ
			stu->showMyOrder();
		}
		else if (select == 3)
		{
			//�鿴����ԤԼ
			stu->showAllOrder();
		}
		else if (select == 4)
		{
			//ȡ��ԤԼ
			stu->cancelOrder();
		}
		else
		{
			delete student;
			cout << "ע���ɹ���" << endl;
			//system("pause");
			//system("cls");
			return;
		}
	}
}

//�����ʦ�Ӳ˵�
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
			//�鿴����ԤԼ
			tea->showAllOrder();

		}
		else if (select == 2)
		{
			//���ԤԼ

			tea->validOrder();
		}
		else
		{
			delete teacher;
			cout << "ע���ɹ���" << endl;
			return;
		}
	}
}

void loginIn(string fileName, int type)
{
	//����ָ������ָ������ �γɶ�̬
	Identity* person = NULL;

	ifstream ifs(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	int id;
	string name;
	string pwd;

	if (type == 1)
	{
		//ѧ��
		cout << "���������ѧ�ţ�" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "���������ְ���ţ�" << endl;
		cin >> id;
	}

	cout << "�������û�����" << endl;
	cin >> name;
	cout << "���������룺" << endl;
	cin >> pwd;
	if (type == 1)
	{
		//ѧ��
		int fid;
		string fname;
		string fpwd;
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fname == name && fpwd == pwd)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;
				person = new Student(id, name, pwd);
				system("pause");
				system("cls");
				//����ѧ���Ӳ˵�
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ
		int fid;
		string fname;
		string fpwd;
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fname == name && fpwd == pwd)
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				person = new Teacher(id, name, pwd);
				system("pause");
				system("cls");
				//������ʦ�Ӳ˵�
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա
		string fname;
		string fpwd;
		while (ifs >> fname && ifs >> fpwd)
		{
			if (fname == name && fpwd == pwd)
			{
				cout << "����Ա��֤��¼�ɹ���" << endl;
				person = new Manager(name, pwd);
				system("pause");
				system("cls");
				//�������Ա�Ӳ˵�
				managerMenu(person);
				return;
			}
		}
	}
	cout << "��֤��½ʧ�ܣ�" << endl;
}

int main()
{
	int select = 0;
	while (true)
	{
		cout << "====================��ӭʹ�ô��ǲ��ͻ���ԤԼϵͳ============================" << endl;
		cout << endl << "������������ݣ�" << endl;
		cout << "\t\t--------------------------------------" << endl;
		cout << "\t\t|                                    |" << endl;
		cout << "\t\t|             1.ѧ������             |" << endl;
		cout << "\t\t|                                    |" << endl;
		cout << "\t\t|             2.��    ʦ             |" << endl;
		cout << "\t\t|                                    |" << endl;
		cout << "\t\t|             3.�� �� Ա             |" << endl;
		cout << "\t\t|                                    |" << endl;
		cout << "\t\t|             0.��    ��             |" << endl;
		cout << "\t\t|                                    |" << endl;
		cout << "\t\t--------------------------------------" << endl;
		cout << "����������ѡ��" << endl;
		cin >> select;
		switch (select)
		{
		case 1://ѧ����¼
			loginIn(STUDENT_FILE, 1);
			break;
		case 2://��ʦ��¼
			loginIn(TEACHER_FILE, 2);
			break;
		case 3://����Ա��¼
			loginIn(ADMIN_FILE, 3);
			break;
		case 0://�˳�
			cout << "��ӭ�´�ʹ�ã�" << endl;
			return 0;
			break;
		default:
			cout << "�����������������룡" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}
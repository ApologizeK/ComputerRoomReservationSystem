#include"teacher.h"
#include "orderFile.h"


//Ĭ�Ϲ��캯��
Teacher::Teacher()
{

}

//�вι��캯��
Teacher::Teacher(int empId, string name, string pwd)
{

	this->m_empId = empId;
	this->m_name = name;
	this->m_pwd = pwd;
}

//�˵�����
void Teacher::operMenu()
{
	cout << "��ӭ��ʦ" << this->m_name << "��¼��" << endl;
	cout << "\t\t--------------------------------------" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             1.�鿴����ԤԼ         |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             2.���ԤԼ             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t|             0.ע����¼             |" << endl;
	cout << "\t\t|                                    |" << endl;
	cout << "\t\t--------------------------------------" << endl;
	cout << "����������ѡ��" << endl;
}

//��ʾ����ԤԼ
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++)
	{
		cout << i + 1 << "��";
		cout << "ԤԼ�����ڣ���" << of.m_orderData[i]["date"];
		cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
		cout << " �����ţ�" << of.m_orderData[i]["roomId"];
		string status = " ״̬:";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ��";
		}
		else if (of.m_orderData[i]["status"] == "0")
		{
			status += "ԤԼȡ��";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

//���ԤԼ
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}

	vector<int>v;
	int index = 0;
	cout << "����˵�ԤԼ��¼���£�" << endl;
	for (int i = 0; i < of.m_size; i++)
	{
		if (of.m_orderData[i]["status"] == "1")
		{
			v.push_back(i);
			cout << ++index << "��";
			cout << "ԤԼ�����ڣ���" << of.m_orderData[i]["date"];
			cout << " ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����");
			cout << " ѧ�ţ�" << of.m_orderData[i]["stuId"];
			cout << " ������" << of.m_orderData[i]["stuName"];
			cout << " �����ţ�" << of.m_orderData[i]["roomId"];
			string status = "״̬�������";
			cout << status << endl;
		}
	}
	cout << "��������˵�ԤԼ��¼��0������" << endl;
	int select = 0;
	int ret = 0;
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
				cout << "��������˵Ľ��(1.ͨ�� 2.��ͨ��)" << endl;
				cin >> ret;
				if (ret == 1)
				{
					of.m_orderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_orderData[v[select - 1]]["status"] = "-1";
				}
				of.updateOrder();
				cout << "������" << endl;
				break;
			}
		}
		cout << "�����������������룡";
	}
	system("pause");
	system("cls");
}
#pragma once
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"

class Manager :public Identity
{
public:
	//���캯��
	Manager();

	//�вι���
	Manager(string name, string pwd);

	//�˵�����
	void operMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void cleanFile();

	//��ʼ������
	void initVector();

	//����ظ�
	bool checkRepeat(int id, int type);

	//ѧ������

	vector<Student> vStu;

	//��ʦ����
	vector<Teacher> vTea;

	//��������
	vector<ComputerRoom> vCom;
};
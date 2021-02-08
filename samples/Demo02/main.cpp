//#include "pch.h"
#include <string>
#include <queue>
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;


//����ͳ����
class stati
{
public:
	//Ŀǰ�Ѿ����˶��ٺ�
	static int nowNumber;

	//���ж������Ŷ�
	static int total;

	static void init()
	{
		nowNumber = 0;
		total = 0;
	}
};
int stati::nowNumber;
int stati::total;


//�Ŷӵ��û�
class user
{
private:
	//���Ŷ������
	int number;

	//�����ҵ������
	string businessType;

public:
	user(string businessType)
	{
		this->number = stati::nowNumber;
		this->businessType = businessType;
		//Ŀǰ�Ŷ���������
		stati::nowNumber++;
		//�����Ŷ�����������
		stati::total++;
	}

	//��ȡ���Ŷ������
	int getNumber()
	{
		return this->number;
	}

	//��ȡ���Ŷ���ҵ������
	string getBusinessType()
	{
		return this->businessType;
	}

	//��ȡ���Ŷ���ҵ������
	void getInfo()
	{
		cout << "--------" << endl;
		cout << "��ǰ��ţ�" << getNumber() << endl;
		cout << "ҵ�����ͣ�" << getBusinessType() << endl;
		cout << "--------" << endl;
	}
};


//ҵ������ѡ��
class busiType
{
private:
	//ҵ����������
	static const int typeNum = 2;
	//ҵ����������
	static string allbusinessType[typeNum];

public:
	//ҵ������ѡ��
	static string choose()
	{
		cout << "��ѡ��ҵ�����ͣ�" << endl;

		//�������ҵ������
		for (int i = 0; i < typeNum; i++)
		{
			cout << i + 1 << "." << allbusinessType[i] << endl;
		}

		//�û�����ҵ������
		int cho;
		cin >> cho;

		return allbusinessType[cho - 1];
	}

	static void init()
	{
		allbusinessType[0] = "���";
		allbusinessType[1] = "ȡ��";
	}
};
string busiType::allbusinessType[typeNum];


//�Ŷӹ�����
class numberManager
{
private:
	//�洢�����Ŷ��ߵĶ���
	static queue<user> allNumber;

public:
	//ȡ��
	static user take()
	{
		//ѯ��ҵ������
		string businessType = busiType::choose();
		user u = user(businessType);
		//�����û����󣬽������
		allNumber.push(u);
		//���ظ��û�����
		return u;
	}

	//�к�
	static user call()
	{
		user result = allNumber.front();
		allNumber.pop();
		stati::nowNumber--;
		return result;
	}

	//��ȡ�����Ŷ�������
	static int getTotalNumber()
	{
		return stati::total;
	}

	//��ȡ��ǰ�Ŷ�������
	static int getNowNumber()
	{
		return stati::nowNumber;
	}

	static void init()
	{
		stati::init();
		busiType::init();
	}

	static void clear()
	{
		//��ն���
		while (!allNumber.empty())
			allNumber.pop();

		//��������
		init();
	}
};
queue<user> numberManager::allNumber;


int main()
{
	numberManager::init();

	while (1)
	{
		//��ѡ��
		cout << "***********" << endl;
		cout << "���нк�ϵͳ" << endl;
		cout << "***********" << endl;
		cout << "1.ȡ��" << endl;
		cout << "2.�к�" << endl;
		cout << "3.��ѯ�ȴ�����" << endl;
		cout << "4.��ѯ�Ŷ�������" << endl;
		cout << "5.����ϵͳ" << endl;

		//�û�����ѡ��
		int cho;
		cin >> cho;

		//ִ�ж�Ӧ����
		switch (cho)
		{
		case 1:
		{
			user u = numberManager::take();

			//�����Ϣ
			u.getInfo();

			cout << "ȡ�ųɹ���" << endl;
			break;
		}

		case 2:
		{
			user u = numberManager::call();

			//�����Ϣ
			u.getInfo();

			cout << "�кųɹ���" << endl;
			break;
		}

		case 3:
		{
			cout << "Ŀǰ�ȴ�����Ϊ��" << numberManager::getNowNumber() << endl;
			break;
		}

		case 4:
		{
			cout << "Ŀǰ�Ŷ�����Ϊ��" << numberManager::getTotalNumber() << endl;
			break;
		}

		case 5:
		{
			numberManager::clear();
			cout << "�������" << endl;
			break;
		}
		}

		_getch();
		system("cls");
	}
}
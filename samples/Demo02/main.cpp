//#include "pch.h"
#include <string>
#include <queue>
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;


//保存统计量
class stati
{
public:
	//目前已经排了多少号
	static int nowNumber;

	//共有多少人排队
	static int total;

	static void init()
	{
		nowNumber = 0;
		total = 0;
	}
};
int stati::nowNumber;
int stati::total;


//排队的用户
class user
{
private:
	//该排队者序号
	int number;

	//处理的业务类型
	string businessType;

public:
	user(string businessType)
	{
		this->number = stati::nowNumber;
		this->businessType = businessType;
		//目前排队人数自增
		stati::nowNumber++;
		//当天排队总人数自增
		stati::total++;
	}

	//获取该排队者序号
	int getNumber()
	{
		return this->number;
	}

	//获取该排队者业务类型
	string getBusinessType()
	{
		return this->businessType;
	}

	//获取该排队者业务类型
	void getInfo()
	{
		cout << "--------" << endl;
		cout << "当前序号：" << getNumber() << endl;
		cout << "业务类型：" << getBusinessType() << endl;
		cout << "--------" << endl;
	}
};


//业务类型选择
class busiType
{
private:
	//业务类型数量
	static const int typeNum = 2;
	//业务类型名称
	static string allbusinessType[typeNum];

public:
	//业务类型选择
	static string choose()
	{
		cout << "请选择业务类型：" << endl;

		//输出所有业务类型
		for (int i = 0; i < typeNum; i++)
		{
			cout << i + 1 << "." << allbusinessType[i] << endl;
		}

		//用户输入业务类型
		int cho;
		cin >> cho;

		return allbusinessType[cho - 1];
	}

	static void init()
	{
		allbusinessType[0] = "存款";
		allbusinessType[1] = "取款";
	}
};
string busiType::allbusinessType[typeNum];


//排队功能类
class numberManager
{
private:
	//存储所有排队者的队列
	static queue<user> allNumber;

public:
	//取号
	static user take()
	{
		//询问业务类型
		string businessType = busiType::choose();
		user u = user(businessType);
		//构造用户对象，进入队列
		allNumber.push(u);
		//返回该用户对象
		return u;
	}

	//叫号
	static user call()
	{
		user result = allNumber.front();
		allNumber.pop();
		stati::nowNumber--;
		return result;
	}

	//获取当天排队总人数
	static int getTotalNumber()
	{
		return stati::total;
	}

	//获取当前排队总人数
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
		//清空队列
		while (!allNumber.empty())
			allNumber.pop();

		//重置其它
		init();
	}
};
queue<user> numberManager::allNumber;


int main()
{
	numberManager::init();

	while (1)
	{
		//主选单
		cout << "***********" << endl;
		cout << "银行叫号系统" << endl;
		cout << "***********" << endl;
		cout << "1.取号" << endl;
		cout << "2.叫号" << endl;
		cout << "3.查询等待人数" << endl;
		cout << "4.查询排队总人数" << endl;
		cout << "5.重置系统" << endl;

		//用户输入选项
		int cho;
		cin >> cho;

		//执行对应操作
		switch (cho)
		{
		case 1:
		{
			user u = numberManager::take();

			//输出信息
			u.getInfo();

			cout << "取号成功！" << endl;
			break;
		}

		case 2:
		{
			user u = numberManager::call();

			//输出信息
			u.getInfo();

			cout << "叫号成功！" << endl;
			break;
		}

		case 3:
		{
			cout << "目前等待人数为：" << numberManager::getNowNumber() << endl;
			break;
		}

		case 4:
		{
			cout << "目前排队人数为：" << numberManager::getTotalNumber() << endl;
			break;
		}

		case 5:
		{
			numberManager::clear();
			cout << "重置完成" << endl;
			break;
		}
		}

		_getch();
		system("cls");
	}
}
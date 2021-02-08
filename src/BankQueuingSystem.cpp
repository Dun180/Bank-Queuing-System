#include <iostream>
#include "Menu.hpp"
using namespace std;



void Menu::mainMenu()
{


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

			//输出信息


			cout << "取号成功！" << endl;
			break;
		}

		case 2:
		{




			cout << "叫号成功！" << endl;
			break;
		}

		case 3:
		{

			break;
		}

		case 4:
		{

			break;
		}

		case 5:
		{

			cout << "重置完成" << endl;
			break;
		}
		}


		system("cls");
	}
}

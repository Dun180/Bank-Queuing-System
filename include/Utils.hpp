// Utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <array>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#define random(a,b) (rand() % (b-a+1))+ a;  //获取[a,b]的随机整数
using namespace std;
/*
* 工具类
*/
class Utils{
private:
    static int line;
public:
    void static writeChar(int x, int y, string pchar, char color);//输出
    void static cleanConsole(int xStart,int xEnd, int y);//清空指定内容
    void static printLog(string log);//打印日志

};
int Utils::line = 20;

void Utils::printLog(string log){
    Utils::writeChar(5, Utils::line,log, 15);
    Utils::line++;
}

void Utils::writeChar(int x, int y, string pchar, char color)
{
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

    COORD loc = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout << pchar;
}
void Utils::cleanConsole(int xStart,int xEnd, int y)
{
    COORD loc;
    loc.Y = y;
    for (int i = xStart; i < xEnd; i++)
    {
        loc.X = i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
        cout << " " << endl;
        ;
    }
}

#endif
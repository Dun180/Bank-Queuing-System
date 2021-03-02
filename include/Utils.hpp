// Utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <thread>
#include <mutex>
#include "ylog.hpp"
#define random(a,b) (rand() % (b-a+1))+ a;  //获取[a,b]的随机整数
using namespace std;

char ylogNull = '\0';
/*
* 工具类
*/
class Utils{
private:
    static int line;
public:
    void static writeChar(short x, short y, string pchar, char color);//输出
    void static cleanConsole(short xStart,short xEnd, short y);//清空指定内容
    void static printLog(string log);//打印日志
    void static chooseUtil(int &option, int &key, bool &flag, vector<string> &options);
    YLog static ylog;
};
int Utils::line = 20;

YLog Utils::ylog(YLog::INFO, "../log/log.txt", YLog::OVER);

void Utils::printLog(string log){
    Utils::writeChar(5, Utils::line,log, 15);
    Utils::line++;
}

void Utils::writeChar(short x, short y, string pchar, char color)
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
void Utils::cleanConsole(short xStart,short xEnd, short y)
{
    COORD loc;
    loc.Y = y;
    for (short i = xStart; i < xEnd; i++)
    {
        loc.X = i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
        cout << " " << endl;
        ;
    }
}
void Utils::chooseUtil(int &option, int &key, bool &flag, vector<string> &options){
    while (true)
    {
        if (kbhit())
        {
            char ch;
            ch = getch();
            if (ch == 27)
            {
                exit(0);
            }
            if (ch == 72 || ch == 80 || ch == '\r')
            {
                if (ch == 72)
                {
                    Utils::writeChar(3, 3 + option, "  ", 0);
                    option--;
                }
                else if (ch == 80)
                {
                    Utils::writeChar(3, 3 + option, "  ", 0);
                    option++;
                }
                if (option < 0)
                {
                    option = 0;
                }
                else if (option >= options.size())
                {
                    option--;
                }
                Utils::writeChar(3, 3 + option, "                         ", 0);
                Sleep(100);
                Utils::writeChar(3, 3 + option, "→", 15);
                Utils::writeChar(5, 3 + option, options[option], 15);

                if (ch == '\r')
                {
                    key = option;
                    flag = true;
                }
            }
        }
        if (flag)
            break;
    }

}

#endif
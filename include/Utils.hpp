// Utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <array>
#include <conio.h>
#include <windows.h>
using namespace std;
/*
* 工具类
*/
class Utils{
public:
    void static writeChar(int x, int y, string pchar, char color);
    void static cleanConsole(int x, int y);


};
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
void Utils::cleanConsole(int x, int y)
{
    COORD loc;
    loc.Y = y;
    for (int i = 0; i < x; i++)
    {
        loc.X = i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
        cout << " " << endl;
        ;
    }
}

#endif
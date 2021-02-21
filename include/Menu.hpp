
// Menu.hpp
#ifndef MENU_HPP
#define MENU_HPP
#include <iostream>
#include <array>
#include <conio.h>
#include <windows.h>
using namespace std;
class Menu{
    public:
    void static mainMenu();
    void static writeChar(int x, int y, string pchar, char color);
    void static cleanConsole(int x, int y);
};

void Menu::mainMenu()
{
    array<string, 3> options = {
        "游客菜单",
        "管理员菜单",
        "退出"};
    system("mode con cols=110 lines=40");
    writeChar(5, 1, "欢迎进入列车时刻查询系统！", 15);
    writeChar(3, 3, "→", 15);
    for (int i = 0; i < options.size(); i++)
    {
        writeChar(5, 3 + i, options[i], 15);
    }
    char ch;
    int option = 0;
    int key = 0;
    bool flag = false;
    while (true)
    {
        if (kbhit())
        {
            ch = getch();
            if (ch == 27)
            {
                exit(0);
            }
            if (ch == 72 || ch == 80 || ch == '\r')
            {
                if (ch == 72)
                {
                    writeChar(3, 3 + option, "  ", 0);
                    option--;
                }
                else if (ch == 80)
                {
                    writeChar(3, 3 + option, "  ", 0);
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
                writeChar(3, 3 + option, "                         ", 0);
                Sleep(100);
                writeChar(3, 3 + option, "→", 15);
                writeChar(5, 3 + option, options[option], 15);

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

    if (key == 0)
    {
    }
    else if (key == 1)
    {
    }
    else if (key == 2)
    {
        exit(0);
    }
    else
    {
        exit(-1);
    }
}

void Menu::writeChar(int x, int y, string pchar, char color)
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
void Menu::cleanConsole(int x, int y)
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
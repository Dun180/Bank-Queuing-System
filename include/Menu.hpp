
// Menu.hpp
#ifndef MENU_HPP
#define MENU_HPP
#include "Utils.hpp"
class Menu{
    public:
    void static mainMenu();
    void static writeChar(int x, int y, string pchar, char color);
    void static cleanConsole(int x, int y);
};

void Menu::mainMenu()
{
    array<string, 3> options = {
        "��ʼģ��",
        "ȡ��",
        "�˳�"};
    system("mode con cols=110 lines=40");//�涨��С
    Utils::writeChar(5, 1, "��ӭ���������Ŷ�ģ��ϵͳ��", 15);
    Utils::writeChar(3, 3, "��", 15);
    Utils::writeChar(5, 8, "�Ŷ�������", 15);
    Utils::writeChar(5, 9, "Ԥ�Ƶȴ�ʱ�䣺", 15);
    Utils::writeChar(5, 11, "һ�Ź�̨", 15);
    Utils::writeChar(15, 11, "���Ź�̨", 15);
    Utils::writeChar(25, 11, "���Ź�̨", 15);
    Utils::writeChar(35, 11, "VIP��̨", 15);
    for (int i = 0; i < options.size(); i++)
    {
        Utils::writeChar(5, 3 + i, options[i], 15);
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
                Utils::writeChar(3, 3 + option, "��", 15);
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




#endif

// Menu.hpp
#ifndef MENU_HPP
#define MENU_HPP
#include "Utils.hpp"
#include "Function.hpp"
class Menu{
    public:
    void static mainMenu();

};

void Menu::mainMenu()
{
    array<string, 5> options = {
        "取号",
        "叫号",
        "叫号1",
        "开始模拟",
        "退出"};
    system("mode con cols=110 lines=40");//规定大小
    Utils::writeChar(5, 1, "欢迎进入银行排队模拟系统！", 15);
    Utils::writeChar(3, 3, "→", 15);
    Utils::writeChar(5, 8, "排队人数：", 15);
    Utils::writeChar(5, 9, "预计等待时间：", 15);
    Utils::writeChar(5, 11, "一号柜台", 15);
    Utils::writeChar(15, 11, "二号柜台", 15);
    Utils::writeChar(25, 11, "三号柜台", 15);
    Utils::writeChar(35, 11, "VIP柜台", 15);
    for (int i = 0; i < options.size(); i++)
    {
        Utils::writeChar(5, 3 + i, options[i], 15);
    }
    Function *function = new Function;
    int key = 0;
    char ch;
    int option = 0;
    do{
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




    if (key == 0)
    {
        function->getNumber();
    }
    else if (key == 1)
    {
        function->callNumber();
    }
    else if (key == 2)
    {
        function->multithreading();
    }
    else if (key == 3){
        function->createSimulation();
    }
    else if (key == 4){
        exit(0);
    }
    else
    {
        exit(-1);
    }
    }while(1);
}




#endif
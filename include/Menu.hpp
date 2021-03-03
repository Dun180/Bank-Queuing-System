
// Menu.hpp
#ifndef MENU_HPP
#define MENU_HPP
#include "Utils.hpp"
#include "Function.hpp"
class Menu{
    private:
    Function *function = NULL;
    public:
    Menu(){
        function = new Function();
    }
    void mainMenu();
    void vipMenu();

};

void Menu::mainMenu()
{
    vector<string> options = {
        "取号",
        "叫号",
        "开始模拟",
        "退出"};
    system("mode con cols=110 lines=40");//规定大小
    Utils::writeChar(5, 1, "欢迎进入银行排队模拟系统！", 15);
    Utils::writeChar(3, 3, "→", 15);
    Utils::writeChar(5, 8, "排队人数：", 15);
    Utils::writeChar(35, 8, "VIP通道人数：", 15);
    Utils::writeChar(5, 9, "预计等待时间：", 15);
    Utils::writeChar(5, 11, "一号柜台", 15);
    Utils::writeChar(15, 11, "二号柜台", 15);
    Utils::writeChar(25, 11, "三号柜台", 15);
    Utils::writeChar(35, 11, "VIP柜台", 15);
    for (int i = 0; i < options.size(); i++)
    {
        Utils::writeChar(5, 3 + i, options[i], 15);
    }
    int key = 0;
    int option = 0;
    do{
        bool flag = false;
        Utils::chooseUtil(option, key, flag, 3, 3, options);
    
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
            vipMenu();
        }
        else if (key == 3){
            exit(0);
        }
        else
        {
            exit(-1);
        }
    }while(1);
}
void Menu::vipMenu()
{
    vector<string> options = {
        "普通客户",
        "vip客户"
        };
    Utils::writeChar(3, 5, "  ", 15);
    Utils::writeChar(16, 5, "→", 15);
    for (int i = 0; i < options.size(); i++)
    {
        Utils::writeChar(18, 5 + i, options[i], 15);
    }
    int key = 0;
    int option = 0;
    do{
        bool flag = false;
        Utils::chooseUtil(option, key, flag, 16, 5, options);
    
        if (key == 0)
        {
            function->multithreading();
        }
        else if (key == 1)
        {
            function->vipWindow();
        }
        else
        {
            exit(-1);
        }
    }while(1);
}




#endif
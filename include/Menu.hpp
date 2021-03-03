
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
        "ȡ��",
        "�к�",
        "��ʼģ��",
        "�˳�"};
    system("mode con cols=110 lines=40");//�涨��С
    Utils::writeChar(5, 1, "��ӭ���������Ŷ�ģ��ϵͳ��", 15);
    Utils::writeChar(3, 3, "��", 15);
    Utils::writeChar(5, 8, "�Ŷ�������", 15);
    Utils::writeChar(35, 8, "VIPͨ��������", 15);
    Utils::writeChar(5, 9, "Ԥ�Ƶȴ�ʱ�䣺", 15);
    Utils::writeChar(5, 11, "һ�Ź�̨", 15);
    Utils::writeChar(15, 11, "���Ź�̨", 15);
    Utils::writeChar(25, 11, "���Ź�̨", 15);
    Utils::writeChar(35, 11, "VIP��̨", 15);
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
        "��ͨ�ͻ�",
        "vip�ͻ�"
        };
    Utils::writeChar(3, 5, "  ", 15);
    Utils::writeChar(16, 5, "��", 15);
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
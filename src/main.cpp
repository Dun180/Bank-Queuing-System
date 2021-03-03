#include <iostream>
#include "../include/Menu.hpp"
using namespace std;
int main(){
    srand((int)time(0));  // 产生随机种子
    Menu menu;
    menu.mainMenu();
}
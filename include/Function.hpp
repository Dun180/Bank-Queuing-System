// Function.hpp
#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include "Utils.hpp"
#include "Customer.hpp"
#include "Queue.hpp"
/*
* 排队功能实现类
*/
class Function{
    private:
    static int number;  //编号
    static int numberOfLine;//排队人数
    static int waitTime;   //等待时间
    Queue<Customer> *wait = NULL;   //排队等待队列
    Customer *counter1 = NULL;  //一号柜台
    Customer *counter2 = NULL;  //二号柜台
    Customer *counter3 = NULL;  //三号柜台
    Customer *counterVip = NULL;  //Vip柜台
    public:
    Function();
    void getNumber();   //取号
    Customer *getCustomerNumber();   //取号(返回Customer对象)
    void callNumber();  //叫号(柜台未满时)
    void callNumber(int num);  //叫号
    void simulation();  //模拟
};
Function::Function(){
    wait = new Queue<Customer>; //初始化队列
}
//从1号开始取号
int Function::number = 1;
//排队人数
int Function::numberOfLine = 0;
//等待时间
int Function::waitTime = 0;
//取号
void Function::getNumber(){
    Customer *customer = new Customer(false,number);    //创建Customer对象
    number++;   //number递增
    numberOfLine++; //排队人数增加
    Utils::cleanConsole(14,20,8);//清除上一个数据
    Utils::writeChar(15, 8, to_string(numberOfLine), 15);//打印排队人数
    wait->enQueue(customer);   //入等待队列
}

//取号(返回Customer对象)
Customer *Function::getCustomerNumber(){
    Customer *customer = new Customer(false,number);    //创建Customer对象
    number++;   //number递增
    numberOfLine++; //排队人数增加
    Utils::cleanConsole(14,20,8);//清除上一个数据
    Utils::writeChar(15, 8, to_string(numberOfLine), 15);//打印排队人数
    wait->enQueue(customer);   //入等待队列
    return customer;
}

//叫号(柜台未满时)
void Function::callNumber(){
    if(counter1 == NULL || counter2 == NULL || counter3 == NULL){
    Customer *customer = wait->deQueue(); //出队
    if(customer == NULL){
        Utils::printLog("无等待人员，叫号失败");
        return;
    }
    numberOfLine--; //排队人数减少
    Utils::cleanConsole(14,20,8);//清除上一个数据
    Utils::writeChar(15, 8, to_string(numberOfLine), 15);//打印排队人数
    if(counter1 == NULL){
        counter1 = customer;
        Utils::writeChar(5, 12, customer->getStringNumber(), 15);
    }else if(counter2 == NULL){
        counter2 = customer;
        Utils::writeChar(15, 12, customer->getStringNumber(), 15);
    }else if(counter3 == NULL){
        counter3 = customer;
        Utils::writeChar(25, 12, customer->getStringNumber(), 15);
    }
    }else{
        Utils::printLog("柜台已满，叫号失败");
    }
}

//叫号
void Function::callNumber(int flag){
    Customer *customer = wait->deQueue(); //出队
    if(customer == NULL){
        Utils::printLog("无等待人员，叫号失败");
        return;
    }
    numberOfLine--; //排队人数减少
    Utils::cleanConsole(14,20,8);//清除上一个数据
    Utils::writeChar(15, 8, to_string(numberOfLine), 15);//打印排队人数
    if(flag == 1){
        counter1 = customer;
        Utils::writeChar(5, 12, customer->getStringNumber(), 15);
    }else if(flag == 2){
        counter2 = customer;
        Utils::writeChar(15, 12, customer->getStringNumber(), 15);
    }else if(flag == 3){
        counter3 = customer;
        Utils::writeChar(25, 12, customer->getStringNumber(), 15);
    }
}

//模拟
void Function::simulation(){
    int wait = random(10,20);  //随机生成10~20个排队等待人员
    for(int i = 0; i < wait; i++){
        getNumber();    //取号
        waitTime += random(3,6);    //随机生成3~6秒的等待时间
    }
    Utils::cleanConsole(18,40,9);//清除上一个数据
    Utils::writeChar(19, 9, to_string(waitTime), 15);//打印等待时间
}
#endif
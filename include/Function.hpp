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
    Queue<Customer> *wait = NULL;   //排队等待队列
    Customer *counter1 = NULL;  //一号柜台
    Customer *counter2 = NULL;  //二号柜台
    Customer *counter3 = NULL;  //三号柜台
    Customer *counterVip = NULL;  //Vip柜台
    public:
    Function();
    void getNumber();   //取号
    void callNumber();  //叫号(柜台未满时)
    void callNumber(int num);  //叫号
};
Function::Function(){
    wait = new Queue<Customer>; //初始化队列
}
//从1号开始取号
int Function::number = 1;

//取号
void Function::getNumber(){
    Customer *customer = new Customer(false,number);    //创建Customer对象
    number++;   //number递增
    wait->enQueue(customer);   //入等待队列
}

//叫号(柜台未满时)
void Function::callNumber(){
    if(counter1 == NULL || counter2 == NULL || counter3 == NULL){
    Customer *customer = wait->deQueue(); //出队
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
        cout<<"柜台已满，叫号失败"<< endl;
    }
}

//叫号
void Function::callNumber(int flag){
    Customer *customer = wait->deQueue(); //出队
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
#endif
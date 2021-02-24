// Customer.hpp
#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include "Utils.hpp"
/*
* 顾客类
*/
class Customer
{
private:
    bool isVip;          //是否为vip
    int temporaryNumber; //临时编号
    int waitTime;   //等待时间
public:
    Customer() {}
    Customer(bool isVip,int temporaryNumber){
        this->isVip = isVip;
        this->temporaryNumber = temporaryNumber;
        this->waitTime = random(3,6)    //随机生成3~6秒的等待时间
        }
    void setIsVip(bool isVip){this->isVip = isVip;}
    void setTemporaryNumber(int temporaryNumber){this->temporaryNumber = temporaryNumber;}
    string getStringNumber(){return to_string(temporaryNumber);}
};

#endif
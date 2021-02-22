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
public:
    Customer() {}
    Customer(bool isVip,int temporaryNumber){
        this->isVip = isVip;
        this->temporaryNumber = temporaryNumber;
        }
    void setIsVip(bool isVip){this->isVip = isVip;}
    void setTemporaryNumber(int temporaryNumber){this->temporaryNumber = temporaryNumber;}
    string getStringNumber(){return to_string(temporaryNumber);}
};

#endif
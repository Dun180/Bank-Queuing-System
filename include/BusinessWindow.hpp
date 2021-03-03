// BusinessWindow.hpp
#ifndef BUSINESSWINDOW_HPP
#define BUSINESSWINDOW_HPP
#include "Utils.hpp"
#include "Customer.hpp"
/*
* 业务窗口类
*/
class BusinessWindow
{
private:
    bool isVip;   //是否为VIP
    bool isNull; //是否为空
    int number; //窗口编号
    Customer *customer; //正在办理业务的顾客
    int evaluateSum; //评价总分
    int evaluateTime; //评价次数
public:
    BusinessWindow() {}
    BusinessWindow(int isVip, int number, int evaluateTime, int evaluateSum){
        this->isVip = isVip;
        this->number = number;
        this->customer = NULL;
        this->isNull = true;
        this->evaluateSum = evaluateSum;
        this->evaluateTime = evaluateTime;
        }
    void setIsNull(bool isNull){this->isNull = isNull;}
    void setNumber(int number){this->number = number;}
    void setCustomer(Customer *customer){this->customer = customer;this->isNull = false;}
    void setEvaluate(int evaluate){evaluateSum += evaluate;evaluateTime++;}
    string getStringNumber(){return to_string(number);}
    Customer* getCustomer(){return customer;}
    bool getIsNull(){return isNull;}    
    int getEvaluateSum(){return this->evaluateSum;}
    int getEvaluateTime(){return this->evaluateTime;}
};

#endif
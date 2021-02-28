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
    bool isVip;  //是否为vip窗口
    bool isNull; //是否为空
    int number; //窗口编号
    Customer *customer; //正在办理业务的顾客
public:
    BusinessWindow() {}
    BusinessWindow(bool isVip,int number){
        this->isVip = isVip;
        this->number = number;
        this->customer = NULL;
        this->isNull = true;
        }
    void setIsVip(bool isVip){this->isVip = isVip;}
    void setIsNull(bool isNull){this->isNull = isNull;}
    void setNumber(int number){this->number = number;}
    void setCustomer(Customer *customer){this->customer = customer;this->isNull = false;}
    string getStringNumber(){return to_string(number);}
    Customer* getCustomer(){return customer;}
    bool getIsVip(){return isVip;}
    bool getIsNull(){return isNull;}

};

#endif
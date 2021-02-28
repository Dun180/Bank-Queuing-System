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
    YLog ylog;  //日志
    mutex m;    //创建互斥锁对象
    vector<thread> wins_thread;//线程窗口 每个线程对应下标相同的窗口
    public:
    Function();
    void getNumber();   //取号
    Customer *getCustomerNumber();   //取号(返回Customer对象)
    void callNumber();  //叫号(柜台未满时)
    void callNumber(int num);  //叫号
    void callNumberAccordingToTime(); //根据时间叫号
    void createSimulation();  //创建模拟
    void transactionProcessing(int flag);   //事务处理
    void multithreading();   //多个事务同时处理
};
Function::Function():ylog(YLog::INFO, "../log/log.txt", YLog::OVER){
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
        this->ylog.W(__FILE__, __LINE__, YLog::INFO, "无等待人员，叫号失败",ylogNull);
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
        this->ylog.W(__FILE__, __LINE__, YLog::INFO, "柜台已满，叫号失败",ylogNull);
    }
}

//叫号
void Function::callNumber(int flag){
    Customer *customer = wait->deQueue(); //出队
    if(customer == NULL){
        Utils::printLog("无等待人员，叫号失败");
        this->ylog.W(__FILE__, __LINE__, YLog::INFO, "无等待人员，叫号失败",ylogNull);
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

//创建模拟
void Function::createSimulation(){
    int wait = random(10,20);  //随机生成10~20个排队等待人员
    for(int i = 0; i < wait; i++){
        getNumber();    //取号
        waitTime += random(3,6);    //随机生成3~6秒的等待时间
    }
    Utils::cleanConsole(18,40,9);//清除上一个数据
    Utils::writeChar(19, 9, to_string(waitTime), 15);//打印等待时间
}

//根据时间叫号
void Function::callNumberAccordingToTime(){
    Customer *customer = wait->getFront()->data;    //获取将要出队的顾客对象
    if(customer == NULL){
        Utils::printLog("无等待人员，叫号失败");
        this->ylog.W(__FILE__, __LINE__, YLog::INFO, "无等待人员，叫号失败",ylogNull);
        return;
    }
    Sleep(1000*customer->getWaitTime());    //等候顾客处理事务
}

//事务处理
void Function::transactionProcessing(int flag){
    this->ylog.W(__FILE__, __LINE__, YLog::INFO, "线程开始",flag);

    //判断柜台是否为空



    do{
    //lock_guard<mutex> guard(m);  //创建lock_guard的类对象guard，用互斥量m来构造
    //默认开始时柜台已满
    //判断执行工作的柜台
    Customer *counter = NULL;
    if(flag == 1){
        counter = counter1;
    }else if(flag == 2){
        counter = counter2;
    }else if(flag == 3){
        counter = counter3;
    }
    //等待当前柜台人员办理业务
    Sleep(1000*counter->getWaitTime());
    delete(counter);
    Customer *customer = wait->getFront()->data;    //获取将要出队的顾客对象
    if(customer == NULL){
        Utils::printLog("无等待人员，叫号失败");
        this->ylog.W(__FILE__, __LINE__, YLog::INFO, "无等待人员，叫号失败",ylogNull);
        break;
    }
    wait->deQueue();//出队
    numberOfLine--; //排队人数减少
    {
        lock_guard<mutex> guard(m);  //创建lock_guard的类对象guard，用互斥量m来构造
        Utils::cleanConsole(14,20,8);//清除上一个数据
        Utils::writeChar(15, 8, to_string(numberOfLine), 15);//打印排队人数
    }
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

    }while(wait->getFront()->data != NULL);
}

void Function::multithreading(){

        for (int i = 1; i < 4; i++)
    {
        //printf("窗口%d就绪\n",i+1);
        wins_thread.emplace_back(std::thread(&Function::transactionProcessing,this,i));
        //std::condition_variable temp;
        //conds.push_back(temp);
    }
    //thread th1(&transactionProcessing,this,1);
    //thread th2(&transactionProcessing,this,2);
    //transactionProcessing(3);
    
    //中止线程
        for (int i = 0; i < wins_thread.size(); i++)
    {
        wins_thread[i].join();
        
    }
    //th1.join();
    //th2.join();


}
#endif
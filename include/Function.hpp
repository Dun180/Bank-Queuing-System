// Function.hpp
#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include "Utils.hpp"
#include "Customer.hpp"
#include "Queue.hpp"
/*
* �Ŷӹ���ʵ����
*/
class Function{
    private:
    static int number;  //���
    static int numberOfLine;//�Ŷ�����
    static int waitTime;   //�ȴ�ʱ��
    Queue<Customer> *wait = NULL;   //�Ŷӵȴ�����
    Customer *counter1 = NULL;  //һ�Ź�̨
    Customer *counter2 = NULL;  //���Ź�̨
    Customer *counter3 = NULL;  //���Ź�̨
    Customer *counterVip = NULL;  //Vip��̨
    YLog ylog;  //��־
    mutex m;    //��������������
    vector<thread> wins_thread;//�̴߳��� ÿ���̶߳�Ӧ�±���ͬ�Ĵ���
    public:
    Function();
    void getNumber();   //ȡ��
    Customer *getCustomerNumber();   //ȡ��(����Customer����)
    void callNumber();  //�к�(��̨δ��ʱ)
    void callNumber(int num);  //�к�
    void callNumberAccordingToTime(); //����ʱ��к�
    void createSimulation();  //����ģ��
    void transactionProcessing(int flag);   //������
    void multithreading();   //�������ͬʱ����
};
Function::Function():ylog(YLog::INFO, "../log/log.txt", YLog::OVER){
    wait = new Queue<Customer>; //��ʼ������
}
//��1�ſ�ʼȡ��
int Function::number = 1;
//�Ŷ�����
int Function::numberOfLine = 0;
//�ȴ�ʱ��
int Function::waitTime = 0;
//ȡ��
void Function::getNumber(){
    Customer *customer = new Customer(false,number);    //����Customer����
    number++;   //number����
    numberOfLine++; //�Ŷ���������
    Utils::cleanConsole(14,20,8);//�����һ������
    Utils::writeChar(15, 8, to_string(numberOfLine), 15);//��ӡ�Ŷ�����
    wait->enQueue(customer);   //��ȴ�����
}

//ȡ��(����Customer����)
Customer *Function::getCustomerNumber(){
    Customer *customer = new Customer(false,number);    //����Customer����
    number++;   //number����
    numberOfLine++; //�Ŷ���������
    Utils::cleanConsole(14,20,8);//�����һ������
    Utils::writeChar(15, 8, to_string(numberOfLine), 15);//��ӡ�Ŷ�����
    wait->enQueue(customer);   //��ȴ�����
    return customer;
}

//�к�(��̨δ��ʱ)
void Function::callNumber(){
    if(counter1 == NULL || counter2 == NULL || counter3 == NULL){
    Customer *customer = wait->deQueue(); //����
    if(customer == NULL){
        Utils::printLog("�޵ȴ���Ա���к�ʧ��");
        this->ylog.W(__FILE__, __LINE__, YLog::INFO, "�޵ȴ���Ա���к�ʧ��",ylogNull);
        return;
    }
    numberOfLine--; //�Ŷ���������
    Utils::cleanConsole(14,20,8);//�����һ������
    Utils::writeChar(15, 8, to_string(numberOfLine), 15);//��ӡ�Ŷ�����
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
        Utils::printLog("��̨�������к�ʧ��");
        this->ylog.W(__FILE__, __LINE__, YLog::INFO, "��̨�������к�ʧ��",ylogNull);
    }
}

//�к�
void Function::callNumber(int flag){
    Customer *customer = wait->deQueue(); //����
    if(customer == NULL){
        Utils::printLog("�޵ȴ���Ա���к�ʧ��");
        this->ylog.W(__FILE__, __LINE__, YLog::INFO, "�޵ȴ���Ա���к�ʧ��",ylogNull);
        return;
    }
    numberOfLine--; //�Ŷ���������
    Utils::cleanConsole(14,20,8);//�����һ������
    Utils::writeChar(15, 8, to_string(numberOfLine), 15);//��ӡ�Ŷ�����
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

//����ģ��
void Function::createSimulation(){
    int wait = random(10,20);  //�������10~20���Ŷӵȴ���Ա
    for(int i = 0; i < wait; i++){
        getNumber();    //ȡ��
        waitTime += random(3,6);    //�������3~6��ĵȴ�ʱ��
    }
    Utils::cleanConsole(18,40,9);//�����һ������
    Utils::writeChar(19, 9, to_string(waitTime), 15);//��ӡ�ȴ�ʱ��
}

//����ʱ��к�
void Function::callNumberAccordingToTime(){
    Customer *customer = wait->getFront()->data;    //��ȡ��Ҫ���ӵĹ˿Ͷ���
    if(customer == NULL){
        Utils::printLog("�޵ȴ���Ա���к�ʧ��");
        this->ylog.W(__FILE__, __LINE__, YLog::INFO, "�޵ȴ���Ա���к�ʧ��",ylogNull);
        return;
    }
    Sleep(1000*customer->getWaitTime());    //�Ⱥ�˿ʹ�������
}

//������
void Function::transactionProcessing(int flag){
    this->ylog.W(__FILE__, __LINE__, YLog::INFO, "�߳̿�ʼ",flag);

    //�жϹ�̨�Ƿ�Ϊ��



    do{
    //lock_guard<mutex> guard(m);  //����lock_guard�������guard���û�����m������
    //Ĭ�Ͽ�ʼʱ��̨����
    //�ж�ִ�й����Ĺ�̨
    Customer *counter = NULL;
    if(flag == 1){
        counter = counter1;
    }else if(flag == 2){
        counter = counter2;
    }else if(flag == 3){
        counter = counter3;
    }
    //�ȴ���ǰ��̨��Ա����ҵ��
    Sleep(1000*counter->getWaitTime());
    delete(counter);
    Customer *customer = wait->getFront()->data;    //��ȡ��Ҫ���ӵĹ˿Ͷ���
    if(customer == NULL){
        Utils::printLog("�޵ȴ���Ա���к�ʧ��");
        this->ylog.W(__FILE__, __LINE__, YLog::INFO, "�޵ȴ���Ա���к�ʧ��",ylogNull);
        break;
    }
    wait->deQueue();//����
    numberOfLine--; //�Ŷ���������
    {
        lock_guard<mutex> guard(m);  //����lock_guard�������guard���û�����m������
        Utils::cleanConsole(14,20,8);//�����һ������
        Utils::writeChar(15, 8, to_string(numberOfLine), 15);//��ӡ�Ŷ�����
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
        //printf("����%d����\n",i+1);
        wins_thread.emplace_back(std::thread(&Function::transactionProcessing,this,i));
        //std::condition_variable temp;
        //conds.push_back(temp);
    }
    //thread th1(&transactionProcessing,this,1);
    //thread th2(&transactionProcessing,this,2);
    //transactionProcessing(3);
    
    //��ֹ�߳�
        for (int i = 0; i < wins_thread.size(); i++)
    {
        wins_thread[i].join();
        
    }
    //th1.join();
    //th2.join();


}
#endif
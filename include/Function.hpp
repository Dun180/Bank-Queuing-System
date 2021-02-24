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
    public:
    Function();
    void getNumber();   //ȡ��
    Customer *getCustomerNumber();   //ȡ��(����Customer����)
    void callNumber();  //�к�(��̨δ��ʱ)
    void callNumber(int num);  //�к�
    void simulation();  //ģ��
};
Function::Function(){
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
    }
}

//�к�
void Function::callNumber(int flag){
    Customer *customer = wait->deQueue(); //����
    if(customer == NULL){
        Utils::printLog("�޵ȴ���Ա���к�ʧ��");
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

//ģ��
void Function::simulation(){
    int wait = random(10,20);  //�������10~20���Ŷӵȴ���Ա
    for(int i = 0; i < wait; i++){
        getNumber();    //ȡ��
        waitTime += random(3,6);    //�������3~6��ĵȴ�ʱ��
    }
    Utils::cleanConsole(18,40,9);//�����һ������
    Utils::writeChar(19, 9, to_string(waitTime), 15);//��ӡ�ȴ�ʱ��
}
#endif
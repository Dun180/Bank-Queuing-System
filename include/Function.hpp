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
    Queue<Customer> *wait = NULL;   //�Ŷӵȴ�����
    Customer *counter1 = NULL;  //һ�Ź�̨
    Customer *counter2 = NULL;  //���Ź�̨
    Customer *counter3 = NULL;  //���Ź�̨
    Customer *counterVip = NULL;  //Vip��̨
    public:
    Function();
    void getNumber();   //ȡ��
    void callNumber();  //�к�(��̨δ��ʱ)
    void callNumber(int num);  //�к�
};
Function::Function(){
    wait = new Queue<Customer>; //��ʼ������
}
//��1�ſ�ʼȡ��
int Function::number = 1;

//ȡ��
void Function::getNumber(){
    Customer *customer = new Customer(false,number);    //����Customer����
    number++;   //number����
    wait->enQueue(customer);   //��ȴ�����
}

//�к�(��̨δ��ʱ)
void Function::callNumber(){
    if(counter1 == NULL || counter2 == NULL || counter3 == NULL){
    Customer *customer = wait->deQueue(); //����
    if(counter1 == NULL){
        counter1 == customer;
        Utils::writeChar(5, 12, "һ�Ź�̨", 15);
    }else if(counter2 == NULL){
        counter2 == customer;
    }else if(counter3 == NULL){
        counter3 == customer;
    }
    }else{
        cout<<"��̨�������к�ʧ��"<< endl;
    }
}

//�к�
void Function::callNumber(int num){

}
#endif
// Queue.hpp
#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "Utils.hpp"
/*
* ����
*/
template<class T>
struct Qnode{//���
    T *data;//������
    Qnode<T> *next;//ָ����
};

template<class T>
class Queue{    //����
    public:
    Qnode<T> *front;    //ͷָ��
    Qnode<T> *rear;     //βָ��
    Queue();
    void enQueue(T *data);  //���
    T *deQueue(); //����
    void printQueue();
};

//��ʼ��������
template<class T>
Queue<T>::Queue(){
    Qnode<T> *node = new Qnode<T>;//��ʼ�����
    node->next = NULL;
    node->data = NULL;
    front = node;
    rear = node;
    Utils::printLog("��ʼ���ɹ�");
}

//��������
template<class T>
void Queue<T>::enQueue(T *data){
    //�ж϶����Ƿ�Ϊ��
    if(front == rear && front->data == NULL){//�������Ϊ��
        front->data = data;

    }else{//������в�Ϊ��

        Qnode<T> *node = new Qnode<T>;//��ʼ�����
        node->next = NULL;
        node->data = data;
        rear->next = node;
        rear = node;
    }
    Utils::printLog("��ӳɹ�");
}

//��������
template<class T>
T *Queue<T>::deQueue(){
    //�ж϶����Ƿ�Ϊ��
    if(this->front == this->rear && this->front->data == NULL){//�������Ϊ��
        Utils::printLog("����Ϊ�գ�����ʧ��");
        return NULL;
    }else if(this->front == this->rear){//ֻ��һ�����ʱ
        Customer *customer = this->front->data;
        this->front->data = NULL;
        Utils::printLog("���ӳɹ�(�����");
        return customer;
    }else{//�ж�����ʱ
        Qnode<T> *node = this->front;
        this->front = this->front->next;//����
        Customer *customer = node->data;
        delete node;
        Utils::printLog("���ӳɹ�");
        return customer;
    }
    return NULL;
}

//��������
template<class T>
void Queue<T>::printQueue(){
        //�ж϶����Ƿ�Ϊ��
    if(front == rear && front->data == NULL){//�������Ϊ��
        cout<<"����Ϊ��"<<endl;
    }else{
        cout<<"------------------"<<endl;
        Qnode<T> *node = front;
        do{
        if(node->data != NULL){
            cout<<*(node->data)<<endl;
        }
        if(node->next!=NULL){
            node = node->next;
        }else{
            break;
        }
        }while(1);
        cout<<"--------------------"<<endl;
    }
}
#endif
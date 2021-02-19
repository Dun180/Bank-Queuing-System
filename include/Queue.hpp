// Queue.hpp
#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <iostream>
using namespace std;
/*
* 队列
*/
template<class T>
struct Qnode{//结点
    T *data;//数据域
    Qnode<T> *next;//指针域
};

template<class T>
class Queue{//队列
    public:
    Qnode<T> *front;//头指针
    Qnode<T> *rear;//尾指针
    Queue(){
        Qnode<T> *node = new Qnode<T>;//初始化结点
        node->next = NULL;
        node->data = NULL;
        front = node;
        rear = node;
        // cout<<front<<endl;
        // cout<<rear<<endl;
        cout<<"初始化成功"<<endl;
    }
    void enQueue(T data);
    void deQueue();
    void printQueue();
};
/*
//初始化链队列
template<class T>
void creatQueue(){
    Qnode<T> *node = new Qnode<T>;//初始化结点
    node->next = NULL;
    node->data = NULL;
    front = node;
    rear = node;
    cout<<front<<endl;
    cout<<rear<<endl;
    cout<<"初始化成功"<<endl;
}
*/
//入链队列
template<class T>
void Queue<T>::enQueue(T data){
    //判断队列是否为空
    if(front == rear && front->data == NULL){//如果队列为空
        front->data = &data;

    }else{//如果队列不为空
        cout<<"-------------------";
        Qnode<T> *node = new Qnode<T>;//初始化结点
        node->next = NULL;
        node->data = &data;
        rear->next = node;
        rear = node;
    }
    cout<<"入队成功"<<endl;
}

//出链队列
template<class T>
void Queue<T>::deQueue(){
    //判断队列是否为空
    if(front == rear && front->data == NULL){//如果队列为空
        cout<<"队列为空，出队失败"<< endl;
    }else if(front == rear){//只有一个结点时
        front->data = NULL;
        cout<<"出队成功(单结点"<<endl;
    }else{//有多个结点时
        Qnode<T> *node = front;
        front = front->next;//出队
        delete node;
        cout<<"出队成功"<<endl;
    }
}

//遍历队列
template<class T>
void Queue<T>::printQueue(){
        //判断队列是否为空
    if(front == rear && front->data == NULL){//如果队列为空
        cout<<"队列为空"<<endl;
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
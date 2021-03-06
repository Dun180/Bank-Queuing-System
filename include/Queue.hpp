// Queue.hpp
#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "Utils.hpp"

/*
* 队列
*/
template<class T>
struct Qnode{//结点
    T *data;//数据域
    Qnode<T> *next;//指针域
};

template<class T>
class Queue{    //队列
    private:
    Qnode<T> *front;    //头指针
    Qnode<T> *rear;     //尾指针
    public:
    Queue();
    void enQueue(T *data);  //入队
    T *deQueue(); //出队
    void printQueue();
    Qnode<T> *getFront(){return front;} //获取头指针
};

//初始化链队列
template<class T>
Queue<T>::Queue(){
    Qnode<T> *node = new Qnode<T>;//初始化结点
    node->next = NULL;
    node->data = NULL;
    front = node;
    rear = node;
    Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "初始化成功",ylogNull);
}

//入链队列
template<class T>
void Queue<T>::enQueue(T *data){
    //判断队列是否为空
    if(front == rear && front->data == NULL){//如果队列为空
        front->data = data;

    }else{//如果队列不为空

        Qnode<T> *node = new Qnode<T>;//初始化结点
        node->next = NULL;
        node->data = data;
        rear->next = node;
        rear = node;
    }
    Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "入队成功",ylogNull);

}

//出链队列
template<class T>
T *Queue<T>::deQueue(){
    //判断队列是否为空
    if(this->front == this->rear && this->front->data == NULL){//如果队列为空
        Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "队列为空，出队失败",ylogNull);
        return NULL;
    }else if(this->front == this->rear){//只有一个结点时
        Customer *customer = this->front->data;
        this->front->data = NULL;
        Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "出队成功（单结点",ylogNull);
        return customer;
    }else{//有多个结点时
        Qnode<T> *node = this->front;
        this->front = this->front->next;//出队
        Customer *customer = node->data;
        delete node;
        Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "出队成功",ylogNull);
        return customer;
    }
    return NULL;
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
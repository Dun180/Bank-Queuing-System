// Queue.hpp
#ifndef QUEUE_HPP
#define QUEUE_HPP
/*
* 队列
*/
template<class T>
struct Qnode{//结点
    T *data;//数据域
    Qnode<T> *next;//指针域
};

template<class T>
struct Queue{//队列
    Qnode<T> *front;//头指针
    Qnode<T> *rear;//尾指针
};

//初始化链队列
template<class T>
void creatQueue(Queue<T> *q){
    Qnode<T> *node = new Qnode<T>;//初始化结点
    node->next = null;
    node->data = null;
    q->front = node;
    q->rear = node;
}

//入链队列
template<class T>
void enQueue(Queue<T> *q,T data){
    //判断队列是否为空
    if(q->front == q->rear && q->front->data == null){//如果队列为空
        q->front->data = &data;
    }else{//如果队列不为空
        Qnode<T> *node = new Qnode<T>;//初始化结点
        node->next = null;
        node->data = &data;
        q->rear->next = node;
        q->rear = node;
    }
}

//出链队列
template<class T>
void deQueue(Queue<T> *q){
    //判断队列是否为空
    if(q->front == q->rear && q->front->data == null){//如果队列为空
        cout<<"队列为空，出队失败";
    }else if(q->front == q->rear){//只有一个结点时
        q->front->data == null;
    }else{//有多个结点时
        Qnode<T> *node = q->front;
        q->front = q->front->next;//出队
        delete node;
    }
}

#endif
#include<iostream>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
using namespace std;
int K = 4,N;   //定义银行服务窗口个数和一天的客户人数 
//欢迎界面函数
void welcom(){
    cout<<"*****************************欢迎光临民大银行****************************"<<endl;
    cout<<"银行的营业时间为 9：00 -17：00，请您注意安排自己的时间，欢迎您的再次到来！"<<endl;   
}

//定义链表节点
template<class T>
struct chainNode
{
  //数据成员
  T element;
  chainNode<T> *next;
  //方法
  chainNode(){}
  chainNode(const T& element){
    this->element=element;
  }
  chainNode(const T& element,chainNode<T> *next){
    this->element=element;
    this->next=next;
  } 
};

//定义队列
template<class T>
class queue{
    public:
        queue();       //初始化队列 
        ~queue(){};    //析构函数 
        bool empty(){  //判断队列是否为空 
          return queueSize==0;
        }
        int size(){    //返回队列中元素的个数 
          return queueSize;
        }    
        T& front(){    //返回队列首元素
          return queueFront->element;
        }    
        T& back(){     //返回队列尾元素 
          return queueBack->element;
        }
        chainNode<T> * begin(){
          return queueFront;
        }
        void pop();    //删除首元素 
        void push(const T& theElement);
    private:
        int queueSize;        //队列长度 
        chainNode<T> *queueFront;  //指向队列第一个元素的指针
        chainNode<T> *queueBack;   //指向队列最后一个元素的指针
};
template<class T>
queue<T>::queue(){
    queueFront=queueBack=NULL;
    queueSize=0;
}

template<class T>
void queue<T>::pop(){
    if(queueFront==NULL) {
        cout<<"you queue is empty!";
        return;
    }
    chainNode<T> *nextNode=queueFront->next;
    delete queueFront;
    queueFront=nextNode;
    queueSize--;
}

template<class T>
void queue<T>::push(const T& theElement){
    //申请新元素节点
    chainNode<T> *newNode=new chainNode<T>(theElement,NULL);
    //把新节点插入队尾
    if(queueSize==0)  queueFront=newNode; //队空 
    else  queueBack->next=newNode;        //队非空 
    queueBack=newNode;
    queueSize++;
}

//定义时间 
struct thetime{
    int h;  //时 
    int m;  //分 
};
//定义每个客户的到达银行时间，等待时间，开始办理业务时间，业务处理时间，结束业务时间(离开银行时间)
struct customers{
    struct thetime arrive_time;     //到达银行时间 
    struct thetime wait_time;       //等待时间 
    struct thetime start_time;      //开始办理业务时间 
    int business_time;              //业务处理时间(假设业务处理时间为整数，且处理时间范围为10-40min) 
    struct thetime end_time;        //结束办理业务时间
    int in_bank_number;             //客户进入银行的序号  
	int business;                   //客户办理的业务 
}; 
//展示窗口服务情况
void show_queue(queue<customers> cus_queue[]){
    Sleep(1000); 
    for(int i = 0;i < K;i++) {
        cout<<"窗口"<<i+1<<": ";
        chainNode<customers> *m = cus_queue[i].begin();
        while(m != NULL) {
            cout<<"客户"<<m->element.in_bank_number<<" ";
            m = m -> next;
        }
        cout<<endl; 
    }
    cout<<endl;
} 

//用户到达银行时间表函数 
void customers_time(struct customers &c){
    //随机产生客户到达银行时间 
    c.arrive_time.h=9+rand()%8;
    c.arrive_time.m=rand()%60;
    //随机产生客户业务处理时间
    //c.business_time=10+rand()%31; 
}
//按用户的到达时间将用户的先后顺序进行排序（由于用户的到达时间是随机产生的） 
void customer_sort(customers customer[]){
    int max_time_index;   //记录客户到达的最晚时间对应的下标 
    customers max_time_cus,swap_cus;
    //采用选择排序进行排序 
    for(int i=N-1;i>0;i--)
    {
        max_time_cus=customer[i];
        max_time_index=i;
        //找出到达时间最晚的 
        for(int j=0;j<i;j++)
        {
          if((customer[j].arrive_time.h)*60+customer[j].arrive_time.m > (max_time_cus.arrive_time.h)*60+max_time_cus.arrive_time.m)
          {
            max_time_cus=customer[j];
            max_time_index=j;   
          }
        }
        if(i!=max_time_index){
          //swap部分
          swap_cus=customer[i];
          customer[i]=max_time_cus;
          customer[max_time_index]=swap_cus;            
        } 
    }

} 

//判断客户需要去哪个窗口排队,即算出等待时间最少的队列 
int judge_queue_in(queue<customers> cus_queue[],customers &customer,int each_queue_cus_number[]) {
    //将用户在每个队列需要等待的时间放在一个数组里
    int each_queue_wait_time[K];
    for(int i=0;i<K;i++) {
        //客户的等待时间取决于他队伍最后一个人的结束办理时间 
        int wait_h=cus_queue[i].back().end_time.h-customer.arrive_time.h;
        each_queue_wait_time[i]=wait_h*60+cus_queue[i].back().end_time.m-customer.arrive_time.m;
    }
    //找出需要时间最少的队列
    int min_time_queue_index=0;
    for(int j=1;j<K;j++) {
        if(each_queue_wait_time[j] < each_queue_wait_time[min_time_queue_index])
          min_time_queue_index=j;
    }
    //定义客户的各项数据
    customer.business_time=10+rand()%31;  
    customer.wait_time.h=each_queue_wait_time[min_time_queue_index]/60;
    customer.wait_time.m=each_queue_wait_time[min_time_queue_index]%60;
    customer.start_time.h=cus_queue[min_time_queue_index].back().end_time.h;
    customer.start_time.m=cus_queue[min_time_queue_index].back().end_time.m;
    customer.end_time.h=customer.start_time.h+(customer.start_time.m+customer.business_time)/60;
    customer.end_time.m=(customer.start_time.m+customer.business_time)%60;
    customer.business = rand()%4+1;
    //将客户加入队列
    //对银行关门时间到了，还在办理的客户允许继续办理完业务再离开，还在排队的进马上离开
    if((customer.start_time.h)*60+customer.start_time.m < 17*60) {
         cus_queue[min_time_queue_index].push(customer);
         each_queue_cus_number[min_time_queue_index]++;
    }
    return min_time_queue_index;
} 

//判断下一个客户到来时哪个队列的队首客户是否已经办理完业务，并进行出队
void leave_queue(queue<customers> cus_queue[],customers customer){
    for(int i=0;i<K;i++) {
        while(!cus_queue[i].empty() && (cus_queue[i].front().start_time.h)*60+cus_queue[i].front().start_time.m+
        cus_queue[i].front().business_time <= (customer.arrive_time.h)*60+customer.arrive_time.m)  {
           cout<<"----------客户"<<cus_queue[i].front().in_bank_number<<"离开了窗口"<<i+1<<"----------"<<endl; 
           cus_queue[i].pop();  
        }       
    }
    //show_queue(cus_queue);    
}

//用户进入队列函数
void customers_in_queue(queue<customers> cus_queue[],customers customer[],int each_queue_cus_number[]) {
    //判断哪个窗口是否有空闲的
    int queue_number; 
    for(int i=0;i<N;i++) {
        bool queue_free=false;
        //每次进入队列判断各队首是否已经办理完业务
        leave_queue(cus_queue,customer[i]);
        for(int j=0;j<K;j++) {
          //窗口中有空闲的情况 
          if(cus_queue[j].empty())
          {
             //客户每进入一个队列都需要判断每个队首客户是否已经办理完业务
             customer[i].business_time=10+rand()%31;   
             customer[i].wait_time.h=0;
             customer[i].wait_time.m=0;
             customer[i].start_time.h=customer[i].arrive_time.h;
             customer[i].start_time.m=customer[i].arrive_time.m;
             customer[i].end_time.h=customer[i].start_time.h+(customer[i].start_time.m+customer[i].business_time)/60;
             customer[i].end_time.m=(customer[i].start_time.m+customer[i].business_time)%60;
             customer[i].business = rand()%4+1;
             cus_queue[j].push(customer[i]);
             each_queue_cus_number[j]++;
             queue_free=true;
             cout<<"----------客户"<<customer[i].in_bank_number<<"到达了窗口"<<j+1<<"----------"<<endl;
             cout<<"客户"<<customer[i].in_bank_number<<"需等人数：0"<<endl; 
             break; 
          }
        }
        //窗口中没有空闲的情况
        if(queue_free==false){
            queue_number = judge_queue_in(cus_queue,customer[i],each_queue_cus_number);   //判断哪个队列的等待时间最少
            cout<<"----------客户"<<customer[i].in_bank_number<<"到达了窗口"<<queue_number<<"----------"<<endl;
            cout<<"客户"<<customer[i].in_bank_number<<"需等人数："<<cus_queue[queue_number].size()-1<<endl; 
        }
        show_queue(cus_queue);                      
    }
    //展示最后客户的离开状态 
    leave_queue(cus_queue,customer[N]); 
    show_queue(cus_queue);
}

int main(){
    //srand(time(0));
    srand((unsigned int)time(NULL));  //使每次编译完后产生的随机数不同 
    welcom();   //欢迎界面 
   // cout<<"请输入银行服务窗口的个数：";
   // int>>K;
    cout<<"请输入银行一天的客户人数：";
    cin>>N;
    customers customer[N];
    queue<customers> cus_queue[K];
    int each_queue_cus_number[N];
    for(int i=0;i<N;i++){
        customers_time(customer[i]);       //初始用户时间 
        each_queue_cus_number[i]=0;        //初始窗口服务客户个数 
        cout<<i+1<<" arrive_time: "<<customer[i].arrive_time.h<<": ";
        cout<<customer[i].arrive_time.m<<endl; 
    }
    customer_sort(customer);  //按客户进入银行的先后顺序进行排序 
    cout<<"---------------------------after sort---------------------------"<<endl;
    for(int i=0;i<N;i++){
        //Sleep(2000);
        customer[i].in_bank_number = i + 1;
        cout<<i+1<<" arrive_time: "<<customer[i].arrive_time.h<<": ";
        cout<<customer[i].arrive_time.m<<endl; 
    }
    cout<<"---------------------------begin serve---------------------------"<<endl;
    customers_in_queue(cus_queue,customer,each_queue_cus_number);  //客户进队列 
    cout<<"---------------------------end serve---------------------------"<<endl;
    cout<<"---------------------------after customer in queue---------------------------"<<endl;
    for(int i=0;i<N;i++){
        cout<<i+1<<" start_time: "<<customer[i].start_time.h<<":"<<customer[i].start_time.m<<"\t";
        cout<<i+1<<" end_time: "<<customer[i].end_time.h<<":"<<customer[i].end_time.m<<"\t";
        cout<<i+1<<" bussiness_time: "<<customer[i].business_time<<"min\t";
        cout<<i+1<<"  wait_time: "<<(customer[i].wait_time.h)*60+customer[i].wait_time.m<<" "<<"\t";
        cout<<i+1<< "bussiness:"<< customer[i].business<<endl;
        switch(customer[i].business)
        {
        	case 1:
        		cout<<"取款"<<endl; break;
        	case 2:
        		cout<<"存款"<<endl; break;
        	case 3:
        		cout<<"还贷"<<endl; break;
        	case 4:
        		cout<<"挂失"<<endl; break;
		}
    }
    int max_cus_wait_time=(customer[0].wait_time.h)*60+customer[0].wait_time.m;
    int sum_cus_wait_time=max_cus_wait_time;
    for(int i=1;i<N;i++){
        if((customer[i].wait_time.h)*60+customer[i].wait_time.m > max_cus_wait_time)
            max_cus_wait_time=(customer[i].wait_time.h)*60+customer[i].wait_time.m;
        sum_cus_wait_time+=(customer[i].wait_time.h)*60+customer[i].wait_time.m;
    }
    int actual_cus_numbers=0;
    for(int i=0;i<K;i++){
        cout<<"窗口"<<i+1<<"服务顾客个数: "<<each_queue_cus_number[i]<<endl;
        actual_cus_numbers+=each_queue_cus_number[i];
    }
    cout<<"max_cus_wait_time: "<<max_cus_wait_time<<"min"<<endl;
    cout<<"avg_cus_wait_time: "<<(double)sum_cus_wait_time/actual_cus_numbers<<"min"<<endl; 
    return 0;
}
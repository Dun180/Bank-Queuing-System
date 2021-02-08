#include<iostream>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
using namespace std;
int K = 4,N;   //�������з��񴰿ڸ�����һ��Ŀͻ����� 
//��ӭ���溯��
void welcom(){
    cout<<"*****************************��ӭ�����������****************************"<<endl;
    cout<<"���е�Ӫҵʱ��Ϊ 9��00 -17��00������ע�ⰲ���Լ���ʱ�䣬��ӭ�����ٴε�����"<<endl;   
}

//��������ڵ�
template<class T>
struct chainNode
{
  //���ݳ�Ա
  T element;
  chainNode<T> *next;
  //����
  chainNode(){}
  chainNode(const T& element){
    this->element=element;
  }
  chainNode(const T& element,chainNode<T> *next){
    this->element=element;
    this->next=next;
  } 
};

//�������
template<class T>
class queue{
    public:
        queue();       //��ʼ������ 
        ~queue(){};    //�������� 
        bool empty(){  //�ж϶����Ƿ�Ϊ�� 
          return queueSize==0;
        }
        int size(){    //���ض�����Ԫ�صĸ��� 
          return queueSize;
        }    
        T& front(){    //���ض�����Ԫ��
          return queueFront->element;
        }    
        T& back(){     //���ض���βԪ�� 
          return queueBack->element;
        }
        chainNode<T> * begin(){
          return queueFront;
        }
        void pop();    //ɾ����Ԫ�� 
        void push(const T& theElement);
    private:
        int queueSize;        //���г��� 
        chainNode<T> *queueFront;  //ָ����е�һ��Ԫ�ص�ָ��
        chainNode<T> *queueBack;   //ָ��������һ��Ԫ�ص�ָ��
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
    //������Ԫ�ؽڵ�
    chainNode<T> *newNode=new chainNode<T>(theElement,NULL);
    //���½ڵ�����β
    if(queueSize==0)  queueFront=newNode; //�ӿ� 
    else  queueBack->next=newNode;        //�ӷǿ� 
    queueBack=newNode;
    queueSize++;
}

//����ʱ�� 
struct thetime{
    int h;  //ʱ 
    int m;  //�� 
};
//����ÿ���ͻ��ĵ�������ʱ�䣬�ȴ�ʱ�䣬��ʼ����ҵ��ʱ�䣬ҵ����ʱ�䣬����ҵ��ʱ��(�뿪����ʱ��)
struct customers{
    struct thetime arrive_time;     //��������ʱ�� 
    struct thetime wait_time;       //�ȴ�ʱ�� 
    struct thetime start_time;      //��ʼ����ҵ��ʱ�� 
    int business_time;              //ҵ����ʱ��(����ҵ����ʱ��Ϊ�������Ҵ���ʱ�䷶ΧΪ10-40min) 
    struct thetime end_time;        //��������ҵ��ʱ��
    int in_bank_number;             //�ͻ��������е����  
	int business;                   //�ͻ������ҵ�� 
}; 
//չʾ���ڷ������
void show_queue(queue<customers> cus_queue[]){
    Sleep(1000); 
    for(int i = 0;i < K;i++) {
        cout<<"����"<<i+1<<": ";
        chainNode<customers> *m = cus_queue[i].begin();
        while(m != NULL) {
            cout<<"�ͻ�"<<m->element.in_bank_number<<" ";
            m = m -> next;
        }
        cout<<endl; 
    }
    cout<<endl;
} 

//�û���������ʱ����� 
void customers_time(struct customers &c){
    //��������ͻ���������ʱ�� 
    c.arrive_time.h=9+rand()%8;
    c.arrive_time.m=rand()%60;
    //��������ͻ�ҵ����ʱ��
    //c.business_time=10+rand()%31; 
}
//���û��ĵ���ʱ�佫�û����Ⱥ�˳��������������û��ĵ���ʱ������������ģ� 
void customer_sort(customers customer[]){
    int max_time_index;   //��¼�ͻ����������ʱ���Ӧ���±� 
    customers max_time_cus,swap_cus;
    //����ѡ������������� 
    for(int i=N-1;i>0;i--)
    {
        max_time_cus=customer[i];
        max_time_index=i;
        //�ҳ�����ʱ������� 
        for(int j=0;j<i;j++)
        {
          if((customer[j].arrive_time.h)*60+customer[j].arrive_time.m > (max_time_cus.arrive_time.h)*60+max_time_cus.arrive_time.m)
          {
            max_time_cus=customer[j];
            max_time_index=j;   
          }
        }
        if(i!=max_time_index){
          //swap����
          swap_cus=customer[i];
          customer[i]=max_time_cus;
          customer[max_time_index]=swap_cus;            
        } 
    }

} 

//�жϿͻ���Ҫȥ�ĸ������Ŷ�,������ȴ�ʱ�����ٵĶ��� 
int judge_queue_in(queue<customers> cus_queue[],customers &customer,int each_queue_cus_number[]) {
    //���û���ÿ��������Ҫ�ȴ���ʱ�����һ��������
    int each_queue_wait_time[K];
    for(int i=0;i<K;i++) {
        //�ͻ��ĵȴ�ʱ��ȡ�������������һ���˵Ľ�������ʱ�� 
        int wait_h=cus_queue[i].back().end_time.h-customer.arrive_time.h;
        each_queue_wait_time[i]=wait_h*60+cus_queue[i].back().end_time.m-customer.arrive_time.m;
    }
    //�ҳ���Ҫʱ�����ٵĶ���
    int min_time_queue_index=0;
    for(int j=1;j<K;j++) {
        if(each_queue_wait_time[j] < each_queue_wait_time[min_time_queue_index])
          min_time_queue_index=j;
    }
    //����ͻ��ĸ�������
    customer.business_time=10+rand()%31;  
    customer.wait_time.h=each_queue_wait_time[min_time_queue_index]/60;
    customer.wait_time.m=each_queue_wait_time[min_time_queue_index]%60;
    customer.start_time.h=cus_queue[min_time_queue_index].back().end_time.h;
    customer.start_time.m=cus_queue[min_time_queue_index].back().end_time.m;
    customer.end_time.h=customer.start_time.h+(customer.start_time.m+customer.business_time)/60;
    customer.end_time.m=(customer.start_time.m+customer.business_time)%60;
    customer.business = rand()%4+1;
    //���ͻ��������
    //�����й���ʱ�䵽�ˣ����ڰ���Ŀͻ��������������ҵ�����뿪�������ŶӵĽ������뿪
    if((customer.start_time.h)*60+customer.start_time.m < 17*60) {
         cus_queue[min_time_queue_index].push(customer);
         each_queue_cus_number[min_time_queue_index]++;
    }
    return min_time_queue_index;
} 

//�ж���һ���ͻ�����ʱ�ĸ����еĶ��׿ͻ��Ƿ��Ѿ�������ҵ�񣬲����г���
void leave_queue(queue<customers> cus_queue[],customers customer){
    for(int i=0;i<K;i++) {
        while(!cus_queue[i].empty() && (cus_queue[i].front().start_time.h)*60+cus_queue[i].front().start_time.m+
        cus_queue[i].front().business_time <= (customer.arrive_time.h)*60+customer.arrive_time.m)  {
           cout<<"----------�ͻ�"<<cus_queue[i].front().in_bank_number<<"�뿪�˴���"<<i+1<<"----------"<<endl; 
           cus_queue[i].pop();  
        }       
    }
    //show_queue(cus_queue);    
}

//�û�������к���
void customers_in_queue(queue<customers> cus_queue[],customers customer[],int each_queue_cus_number[]) {
    //�ж��ĸ������Ƿ��п��е�
    int queue_number; 
    for(int i=0;i<N;i++) {
        bool queue_free=false;
        //ÿ�ν�������жϸ������Ƿ��Ѿ�������ҵ��
        leave_queue(cus_queue,customer[i]);
        for(int j=0;j<K;j++) {
          //�������п��е���� 
          if(cus_queue[j].empty())
          {
             //�ͻ�ÿ����һ�����ж���Ҫ�ж�ÿ�����׿ͻ��Ƿ��Ѿ�������ҵ��
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
             cout<<"----------�ͻ�"<<customer[i].in_bank_number<<"�����˴���"<<j+1<<"----------"<<endl;
             cout<<"�ͻ�"<<customer[i].in_bank_number<<"���������0"<<endl; 
             break; 
          }
        }
        //������û�п��е����
        if(queue_free==false){
            queue_number = judge_queue_in(cus_queue,customer[i],each_queue_cus_number);   //�ж��ĸ����еĵȴ�ʱ������
            cout<<"----------�ͻ�"<<customer[i].in_bank_number<<"�����˴���"<<queue_number<<"----------"<<endl;
            cout<<"�ͻ�"<<customer[i].in_bank_number<<"���������"<<cus_queue[queue_number].size()-1<<endl; 
        }
        show_queue(cus_queue);                      
    }
    //չʾ���ͻ����뿪״̬ 
    leave_queue(cus_queue,customer[N]); 
    show_queue(cus_queue);
}

int main(){
    //srand(time(0));
    srand((unsigned int)time(NULL));  //ʹÿ�α������������������ͬ 
    welcom();   //��ӭ���� 
   // cout<<"���������з��񴰿ڵĸ�����";
   // int>>K;
    cout<<"����������һ��Ŀͻ�������";
    cin>>N;
    customers customer[N];
    queue<customers> cus_queue[K];
    int each_queue_cus_number[N];
    for(int i=0;i<N;i++){
        customers_time(customer[i]);       //��ʼ�û�ʱ�� 
        each_queue_cus_number[i]=0;        //��ʼ���ڷ���ͻ����� 
        cout<<i+1<<" arrive_time: "<<customer[i].arrive_time.h<<": ";
        cout<<customer[i].arrive_time.m<<endl; 
    }
    customer_sort(customer);  //���ͻ��������е��Ⱥ�˳��������� 
    cout<<"---------------------------after sort---------------------------"<<endl;
    for(int i=0;i<N;i++){
        //Sleep(2000);
        customer[i].in_bank_number = i + 1;
        cout<<i+1<<" arrive_time: "<<customer[i].arrive_time.h<<": ";
        cout<<customer[i].arrive_time.m<<endl; 
    }
    cout<<"---------------------------begin serve---------------------------"<<endl;
    customers_in_queue(cus_queue,customer,each_queue_cus_number);  //�ͻ������� 
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
        		cout<<"ȡ��"<<endl; break;
        	case 2:
        		cout<<"���"<<endl; break;
        	case 3:
        		cout<<"����"<<endl; break;
        	case 4:
        		cout<<"��ʧ"<<endl; break;
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
        cout<<"����"<<i+1<<"����˿͸���: "<<each_queue_cus_number[i]<<endl;
        actual_cus_numbers+=each_queue_cus_number[i];
    }
    cout<<"max_cus_wait_time: "<<max_cus_wait_time<<"min"<<endl;
    cout<<"avg_cus_wait_time: "<<(double)sum_cus_wait_time/actual_cus_numbers<<"min"<<endl; 
    return 0;
}
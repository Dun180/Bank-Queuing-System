// Function.hpp
#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include "Utils.hpp"
#include "Customer.hpp"
#include "Queue.hpp"
#include "BusinessWindow.hpp"
/*
* �Ŷӹ���ʵ����
*/
class Function{
    private:
    static int number;  //���
    static int numberOfLine;//�Ŷ�����
    static int waitTime;   //�ȴ�ʱ��
    Queue<Customer> *wait = NULL;   //�Ŷӵȴ�����
    BusinessWindow *vipWin = NULL;  //Vip����
    mutex m;    //��������������
    vector<thread> wins_thread;//�̴߳��� ÿ���̶߳�Ӧ�±���ͬ�Ĵ���
    vector<BusinessWindow> wins;//����
    int numOfWindow = 3;    //��������
    int firstWindow = -1;   //������ɵĴ���
    public:
    Function();
    void getNumber();   //ȡ��
    Customer *getCustomerNumber();   //ȡ��(����Customer����)
    void callNumber();  //�к�(��̨δ��ʱ)
    void callNumber(int num);  //�к�
    void callNumberAccordingToTime(); //����ʱ��к�
    void createSimulation();  //����ģ��
    void transactionProcessing(int flag);   //������
    void multithreading();   //���߳�
    void progressBar(int win); //������
    void evaluate(int win);//����
    void sava();//��������
};
Function::Function(){
    wait = new Queue<Customer>; //��ʼ������
    //��ʼ������
    ifstream win_infile("../data/evaluation.txt",ios::in);//���ļ�׼����ȡ
    if(!win_infile){
        Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "�ļ���ȡʧ�ܣ�",ylogNull);
    }
    for(int i=0;i<numOfWindow;i++){
            int evaluateTime = 0; //���۴���
            int evaluateSum = 0; //�����ܷ�
            win_infile >> evaluateTime >> evaluateSum;//��ȡ
            Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "���ڱ��",i+1);
            Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "���۴���",evaluateTime);
            Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "�����ܷ�",evaluateSum);
            BusinessWindow w(i,evaluateTime,evaluateSum);
            wins.emplace_back(w);
    }
    win_infile.close();
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
    Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "�����˿�",customer->getStringNumber());
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

//�к�(����δ��ʱ)
void Function::callNumber(){
    bool flag = false;//�жϴ����Ƿ�δ���ı�־
    //�жϴ����Ƿ�����
    for(int i=0;i<numOfWindow;i++)
        {
            if(wins[i].getIsNull()){
                flag = true;
            }
        }
    if(flag == true){
        Customer *customer = wait->deQueue(); //����
        if(customer == NULL){
            Utils::printLog("�޵ȴ���Ա���к�ʧ��");
            Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "�޵ȴ���Ա���к�ʧ��",ylogNull);
            return;
        }
    numberOfLine--; //�Ŷ���������
    Utils::cleanConsole(14,20,8);//�����һ������
    Utils::writeChar(15, 8, to_string(numberOfLine), 15);//��ӡ�Ŷ�����
    for(int i=0;i<numOfWindow;i++)
        {
            if(wins[i].getIsNull()){
                wins[i].setCustomer(customer);
                Utils::writeChar(5+i*10, 12, customer->getStringNumber(), 15);
                break;
            }
        }
    
    }else{
        Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "�����������˳�",ylogNull);
    }
}

//�к�
void Function::callNumber(int flag){
    Customer *customer = wait->deQueue(); //����
    if(customer == NULL){
        Utils::printLog("�޵ȴ���Ա���к�ʧ��");
        Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "�޵ȴ���Ա���к�ʧ��",ylogNull);
        return;
    }
    numberOfLine--; //�Ŷ���������
    Utils::cleanConsole(14,20,8);//�����һ������
    Utils::writeChar(15, 8, to_string(numberOfLine), 15);//��ӡ�Ŷ�����
    wins[flag].setCustomer(customer);
    Utils::writeChar(5+flag*10, 12, customer->getStringNumber(), 15);

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
 //������
void Function::progressBar(int win){
    Utils::writeChar(5, 3, "����", 15);
    Utils::writeChar(9, 3, to_string(win+1), 15);
    Utils::writeChar(10, 3, "�Ŵ��ڰ���ҵ����", 15);

    Utils::writeChar(5, 5, "[", 15);
    Utils::writeChar(35, 5, "]", 15);
    for(int i = 6; i <35;i++){
        Utils::writeChar(i, 5, "#", 15);
        Sleep(100);
    }
    Utils::writeChar(5, 7, "����ɹ�", 15);
    Sleep(2000);
}


//������
void Function::transactionProcessing(int identifier){
    Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "�߳̿�ʼ",identifier);

    //�жϹ�̨�Ƿ�Ϊ��



    do{
    //lock_guard<mutex> guard(m);  //����lock_guard�������guard���û�����m������
    //Ĭ�Ͽ�ʼʱ��̨����

    //�ȴ���ǰ��̨��Ա����ҵ��
    Sleep(1000*wins[identifier].getCustomer()->getWaitTime());
        Customer *customer = NULL;
    {
        lock_guard<mutex> guard(m);  //����lock_guard�������guard���û�����m������
        customer = wait->getFront()->data;    //��ȡ��Ҫ���ӵĹ˿Ͷ���
        if(customer == NULL){
            Utils::printLog("�޵ȴ���Ա���к�ʧ��");
            Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "�޵ȴ���Ա���к�ʧ��",identifier);
            if(firstWindow < 0){firstWindow = identifier;}
        break;
        }
        wait->deQueue();//����
    }
    
    numberOfLine--; //�Ŷ���������
    {
        lock_guard<mutex> guard(m);  //����lock_guard�������guard���û�����m������
        Utils::cleanConsole(14,20,8);//�����һ������
        Utils::writeChar(15, 8, to_string(numberOfLine), 15);//��ӡ�Ŷ�����
    }

    wins[identifier].setCustomer(customer);
    {
        lock_guard<mutex> guard(m);  //����lock_guard�������guard���û�����m������
        Utils::writeChar(5+10*identifier, 12, customer->getStringNumber(), 15);
        Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, to_string(identifier)+"�Ŵ������ڰ���ҵ��Ĺ˿�Ϊ",customer->getStringNumber());
    }
    }while(wait->getFront()->data != NULL);
}

//����
void Function::evaluate(int win)
{
    system("cls");
    vector<string> options = {
        "��",
        "���",
        "����",
        "�����",
        "������",
        "��������"
        };
    Utils::writeChar(5, 1, "���"+to_string(win+1)+"�Ŵ��ڵķ����������", 15);
    Utils::writeChar(3, 3, "��", 15);
    for (int i = 0; i < options.size(); i++)
    {
        Utils::writeChar(5, 3 + i, options[i], 15);
    }
    int key = 0;
    int option = 0;
    bool flag = false;
    Utils::chooseUtil(option, key, flag, options);
    if (key == 0)
    {
        wins[win].setEvaluate(1);
    }
    else if (key == 1)
    {
        wins[win].setEvaluate(2);
    }
    else if (key == 2)
    {
        wins[win].setEvaluate(3);
    }
    else if (key == 3){
        wins[win].setEvaluate(4);
    }
    else if (key == 4){
        wins[win].setEvaluate(5);
    }
    else if (key == 5){}
    else
    {
        exit(-1);
    }

}

//��������
void Function::sava(){
    ofstream win_outfile("../data/evaluation.txt",ios::out);
    if(!win_outfile){
        Utils::ylog.W(__FILE__, __LINE__, YLog::INFO, "�ļ�д��ʧ�ܣ�",ylogNull);
    }
    vector<BusinessWindow>::iterator t;
    for(t = wins.begin();t != wins.end();++t){
        win_outfile<<t->getEvaluateTime()<<" "<<t->getEvaluateSum()<<"\n";
    }
    win_outfile.close();
}

//���߳�ʵ��
void Function::multithreading(){

    for (int i = 0; i < numOfWindow; i++)
    {
        Function::callNumber();
    }
    
   
        for (int i = 0; i < numOfWindow; i++)
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
    Sleep(5000);
    system("cls");
    progressBar(firstWindow);
    evaluate(firstWindow);//����
    sava();//��������
    //th1.join();
    //th2.join();
    system("cls");
    Utils::writeChar(5, 1, "��л�������ټ���", 15);
    Sleep(3000);
    exit(0);

}
#endif
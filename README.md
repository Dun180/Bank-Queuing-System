## 银行排队模拟系统



##### 存在且尚未解决的问题

多线程使用公共资源时存在问题




##### 尚未实现的功能

1.加入随时间流动自动叫号的功能

2.加入模拟前面排队人数的功能

3.加入评价功能

4.完善vip功能



##### 其他



###### 线程demo：

https://blog.csdn.net/BJUT_bluecat/article/details/89943936



###### 多线程编译命令

 ```shell
g++ -static -std=c++11 -lpthread main.cpp -o main
 ```





###### 日志打印方法

```c++
  YLog ylog(YLog::INFO, "../log/log.txt", YLog::OVER);

  ylog.W(**__FILE__**, **__LINE__**, YLog::INFO, "hello world",ylogNull);
```


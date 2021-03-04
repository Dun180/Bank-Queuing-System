## 银行排队模拟系统

纯命令行实现

##### 存在且尚未解决的问题

有一定概率崩溃，原因未查明

##### 尚未实现的功能





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


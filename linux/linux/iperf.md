## iperf3

#### 测试带宽
- 服务端
iperf3 -s -p 12345 -i 1
iperf3 -s -p 12345

- 客户端
iperf3 -c serverIPAddr -p 12345 -i 1 -t 10 -w 100k
iperf3 -c serverIPAddr -p 12345 -u -b 100m
```C++
-t:设置传输总时间，在指定时间内，重复发送指定长度的数据包，默认10S
-w:设置套接字缓冲区为指定大小
-i：时间间隔
-p:端口号
-s:服务端
-c:客户端



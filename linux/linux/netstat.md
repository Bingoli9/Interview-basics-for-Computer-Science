## netstat

NetStat命令用于显示网络相关信息，如网络连接，路由表，接口状态，masquerade连接，多播成员等。

执行netstat后的输出结果为

```c++
Active Internet connections (w/o servers)
Proto Recv-Q Send-Q Local Address Foreign Address State
tcp 0 2 210.34.6.89:telnet 210.34.6.96:2873 ESTABLISHED
tcp 296 0 210.34.6.89:1165 210.34.6.84:netbios-ssn ESTABLISHED
tcp 0 0 localhost.localdom:9001 localhost.localdom:1162 ESTABLISHED
tcp 0 0 localhost.localdom:1162 localhost.localdom:9001 ESTABLISHED
tcp 0 80 210.34.6.89:1161 210.34.6.10:netbios-ssn CLOSE

Active UNIX domain sockets (w/o servers)
Proto RefCnt Flags Type State I-Node Path
unix 1 [ ] STREAM CONNECTED 16178 @000000dd
unix 1 [ ] STREAM CONNECTED 16176 @000000dc
unix 9 [ ] DGRAM 5292 /dev/log
unix 1 [ ] STREAM CONNECTED 16182 @000000df
```

从整体上看，netstat的输出结果分为两部分：

Active Internet connections 称为有源TCP连接，其中Recv-Q和Send-Q指的是接收队列和发送队列。

另一个是Active UNIX domain socket，称为有源Unix域套接字。

## 常见参数

```c++
-a 显示所有选项，默认不显示LISTEN相关。
-t 仅显示tcp相关选项
-u 仅显示udp相关选项
-l 仅列出有在Listen监听的服务状态
-p 显示建立相关链接的程序名
-r 路由表
-s 按各个协议统计
-c 每隔一段时间执行该netstat命令
```

## 运用

#### 查看连接某服务端口最多的IP地址

```c++
netstat -nat | grep "192.168.1.15:22" |awk '{print $5}'|awk -F: '{print $1}'|sort|uniq -c|sort -nr|head -20
221.136.168.36
154.74.45.242
78.173.31.236
62.183.207.98
192.168.1.14
182.48.111.215
124.193.219.34
119.145.41.2
114.255.41.30
75.102.11.99
```

#### TCP各种状态列表

```c++
netstat -nat |awk '{print $6}'
```


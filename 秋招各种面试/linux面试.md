#### linux内存设计

#### Linux进程间通信方式以及对应的api

1. 无名管道 int pipe(int pipe[2])
2. 信号量 semget/senctl/semop
3. 消息队列 msgget()、msgsnd()、msgrcv()、msgctl()
4. 共享内存 shmget()、shmat()、shmdt()、shmctl()
5. 信号
6. 套接字

#### 通过进程查看其占用的端口号

先查看进程pid: ps -ef | grep 进程名

通过pid查看占用端口： netstat -nap | grep pid

#### 通过端口号查看进程

netstat -nap | grep 端口号

#### 超大文件的字符串排序怎么做

分而治之，先打大文件分词大小均匀的若干个小文件，然后对小文件排好序，最后再Merge所有的小文件，在Merge的过程中去掉重复的内容。

在Linux下实现这个逻辑甚至不用自己写代码，只要用shell内置的一些命令: split, sort就足够了。

#### 将lua5.1升级至lua5.3

ln -s /usr/local/lua/src/lua /usr/bin/lua 创建软连接

#### linux下常用命令

ll pwd touch rm mkdir rmdir mv cp ln cat less more tail vim vimdiff grep tar rz sz df du free top ethtool sar netstat iostat ps ifconfig ping talnet...

```c++
ethtool ethx       //查询ethx网口基本设置，其中 x 是对应网卡的编号，如eth0、eth1等等 
ethtool –h        //显示ethtool的命令帮助(help) 
ethtool –i ethX    //查询ethX网口的相关信息  
ethtool –d ethX    //查询ethX网口注册性信息 
ethtool –r ethX    //重置ethX网口到自适应模式 
ethtool –S ethX    //查询ethX网口收发包统计 
```

tail: 显示指定文件的末尾10行

free：显示内存占用情况

netstat：用于输出有关网络状态的信息

```
-a (all)显示所有选项，netstat默认不显示LISTEN相关
-t (tcp)仅显示tcp相关选项
-u (udp)仅显示udp相关选项
-n 拒绝显示别名，能显示数字的全部转化成数字。(重要)
-l 仅列出有在 Listen (监听) 的服務状态

-p 显示建立相关链接的程序名(macOS中表示协议 -p protocol)
-r 显示路由信息，路由表
-e 显示扩展信息，例如uid等
-s 按各个协议进行统计 (重要)
-c 每隔一个固定时间，执行该netstat命令。
```

iostat：用于输出CPU和磁盘I/O相关的统计信息

```
-c：只显示系统CPU统计信息，即单独输出avg-cpu结果，不包括device结果
-d：单独输出Device结果，不包括cpu结果
-k/-m：输出结果以kB/mB为单位，而不是以扇区数为单位
-x:输出更详细的io设备统计信息
interval/count：每次输出间隔时间，count表示输出次数，不带count表示循环输出
```

sar:用于性能分析

```
-u:整体CPU使用统计
-P：各个CPU使用统计
-r：内存使用情况统计
-b：整体I/O设备情况
-d：各个IO设备情况
-n：网络统计
-o：sar日志保存
```

#### dmesg

dmesg命令设备故障的诊断是非常重要的。在dmesg命令的帮助下进行 硬件的连接或断开连接操作式，我们可以看到硬件的检测或者断开连接的信息。

```
dmesg | more： 列出加载到内核中的所有驱动
dmesg | grep sda： 列出所有被检测到的硬件
dmesg | head  -20：输出dmesg命令的前20行日志
```

#### linux进程间通信

1. 管道

2. 信号

   信号是软件层次上对中断机制的一种模拟，在原理上，一个进程收到一个信号与处理器收到一个中断请求可以说是一样的。信号是异步的，一个进程不必通过任何操作来等待信号的到达，事实上，进程也不知道信号到底什么时候到达。

3. 消息队列

4. 信号量

5. 共享内存

6. 套接字


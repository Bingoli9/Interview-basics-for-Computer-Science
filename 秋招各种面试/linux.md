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

#### ethtool

```c++
ethtool ethx       //查询ethx网口基本设置，其中 x 是对应网卡的编号，如eth0、eth1等等 
ethtool –h        //显示ethtool的命令帮助(help) 
ethtool –i ethX    //查询ethX网口的相关信息  
ethtool –d ethX    //查询ethX网口注册性信息 
ethtool –r ethX    //重置ethX网口到自适应模式 
ethtool –S ethX    //查询ethX网口收发包统计 
```

#### tail

显示指定文件的末尾10行

#### free

显示内存占用情况

#### netstat

用于输出有关网络状态的信息

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

#### iostat

用于输出CPU和磁盘I/O相关的统计信息

```
-c：只显示系统CPU统计信息，即单独输出avg-cpu结果，不包括device结果
-d：单独输出Device结果，不包括cpu结果
-k/-m：输出结果以kB/mB为单位，而不是以扇区数为单位
-x:输出更详细的io设备统计信息
interval/count：每次输出间隔时间，count表示输出次数，不带count表示循环输出
```

#### sar

用于性能分析

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

#### tcpdump

```c++
#抓取所有经过eth0，目的或源地址是92.168.29.162的网络数据
tcpdump -n -i eth0 host 192.168.29.162
# 源地址

命令：tcpdump -i eth1 src host 192.168.29.162

# 目的地址

命令：tcpdump -i eth1 dst host 192.168.29.162

#抓取当前服务器eth0网卡端口8080的网络数据

命令：tcpdump -n -i eth0 port 8080

#打印helios 与 hot 或者与 ace 之间通信的数据包

tcpdump host helios and \( hot or ace \)
   
#对本机的udp 123 端口进行监视
 
tcpdump udp port 123   
```

#### ipcs

#### ipcrm

#### 统计8080端口上有多少个TCP连接

```c++
netstat –nat | grep 8080 | wc –l
```

#### 显示所有运行中的进程

```c++
ps aux | less
```

#### awk

awk是一种编程语言，用于对文本和数据进行处理的

具有强大的文本格式化能力

利用命令awk，可以将一些文本整理成我们想要的样子。

```c++
awk '条件类型1{动作1} 条件类型2{动作2} ...' filename
```

```
awk命令形式:
awk [-F|-f|-v] ‘BEGIN{} //{command1; command2} END{}’ file
 [-F|-f|-v]   大参数，-F指定分隔符，-f调用脚本，-v定义变量 var=value
'  '          引用代码块
BEGIN   初始化代码块，在对每一行进行处理之前，初始化代码，主要是引用全局变量，设置FS分隔符
//           匹配代码块，可以是字符串或正则表达式
{}           命令代码块，包含一条或多条命令
；          多条命令使用分号分隔
END      结尾代码块，在对每一行进行处理之后再执行的代码块，主要是进行最终计算或输出结尾摘要信息
```

#### gdb调试

| 命令           | 命令缩写 | 命令说明                                                     |
| -------------- | -------- | ------------------------------------------------------------ |
| list           | l        | 显示多行源代码                                               |
| break          | b        | 设置断点,程序运行到断点的位置会停下来                        |
| info           | i        | 描述程序的状态                                               |
| run            | r        | 开始运行程序                                                 |
| display        | disp     | 跟踪查看某个变量,每次停下来都显示它的值                      |
| step           | s        | 执行下一条语句,如果该语句为函数调用,则进入函数执行其中的第一条语句 |
| next           | n        | 执行下一条语句,如果该语句为函数调用,不会进入函数内部执行(即不会一步步地调试函数内部语句) |
| print          | p        | 打印内部变量值                                               |
| continue       | c        | 继续程序的运行,直到遇到下一个断点                            |
| set var name=v |          | 设置变量的值                                                 |
| start          | st       | 开始执行程序,在main函数的第一条语句前面停下来                |
| file           |          | 装入需要调试的程序                                           |
| kill           | k        | 终止正在调试的程序                                           |
| watch          |          | 监视变量值的变化                                             |
| backtrace      | bt       | 产看函数调用信息(堆栈)                                       |
| frame          | f        | 查看栈帧                                                     |
| quit           | q        | 退出GDB环境                                                  |

#### 如何定位内存泄漏

命令 mtrace

```c++
#include <stdio.h>
 
int main()
{
        setenv("MALLOC_TRACE", "taoge.log", "1");
        mtrace();
 
        int *p = (int *)malloc(2 * sizeof(int));
 
        return 0;
}
```

   运行：./a.out

   定位：mtrace a.out taoge.log

#### i++是否原子操作？并解释为什么

i++操作分为3步：

（1）栈中取出i

（2）i自增1

（3）将i存到栈

所以不是原子操作

#### linux系统的各类同步机制

1. 互斥锁

2. 条件变量

   满足某个条件时，可通过条件变量通知其他线程do-something；必须与互斥锁联合使用，单独无法执行

3. 读写锁

   针对多读者，少写者的情况设定

#### 实现守护进程



#### linux的内存管理机制

包括物理内存和虚拟内存。虚拟内存是为了满足内存不足而提出的策略，它是利用磁盘空间虚拟出的一块逻辑内存，用作虚拟内存的磁盘空间被称为交换空间。

内核会将暂时不用的内存块信息写到交换空间，物理内存得到释放，当需要原始的内容时，这些信息会被重新从交换空间读入物理内存。

  linux的内存管理采取的是分页存取机制，为了保证物理内存能得到充分的利用，内核会在适当的时候将物理内存中不经常使用的数据块自动交换到虚拟内存中，而将经常使用的信息保留到物理内存。

最后，交换空间的页面在使用时会首先被交换到物理内存，如果此时没有足够的物理内存来容纳这些页面，它们又会被马上交换出去，如此以来，虚拟内存中可能没有足够空间来存储这些交换页面，最终会导致linux出现假死机、服务异常等问题，linux虽然可以在一段时间内自行恢复，但是恢复后的系统已经基本不可用了。

#### linux的任务调度机制



#### 系统如何将一个信号通知到进程



#### 文件目录管理

```c++
ls 浏览目录
chmod	修改文件权限
chown	改变文件所有者
cp	复制文件按
cd	改变当前目录
mv	重命名或移动文件
rm	删除文件或者目录
pwd	当前目录
scp	远程拷贝
alias	别名
find	查找文件
type	查看一个命令所在路径
echo	控制台输出
```

#### 性能监控

```
crontab	制定计划任务，通常用于系统监控
df	查看磁盘生于空间
ps	查看进程状态
top	查看cpu使用率
kill 终止进程
```

#### 目录说明

```
/bin	存放二进制可执行文件，常用命令一般都在这里
/etc	存放系统管理和配置文件
/home	存放所有用户文件的根目录，是用户主目录的几点
/usr	用于存放系统应用程序
/opt	额外安装的可选应用程序包所防止的位置
proc	虚拟文件系统目录，是系统内存的映射。可直接访问这个目录来获取系统信息
/sbin	存放二进制可执行文件。存放的是系统管理员使用的系统级别的管理命令和程序
/dev	用于存放设备文件
/mnt	系统管理员安装临时文件系统的安装点，系统提供这个目录是让用户临时挂在其他文件系统
/boot	存放用于系统引导时使用的各种文件
/lib	存放着和系统运行相关的库文件
/tmp	存放临时文件
/var	存放运行时寻妖改变数据的文件，也是某些大文件的溢出区
```


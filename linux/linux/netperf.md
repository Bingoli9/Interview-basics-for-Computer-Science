## netperf

#### 网络性能测试五项指标
- 可用性
- 响应时间
- 网络利用率
- 网络吞吐量
- 网络带宽容量

#### 收集网络性能数据方式
- 通过snmp协议直接到网络设备获取， 如net-snmp工具
- 侦听相关网络性能数据， 典型工具tcpdump
- 自行产生相应的测试数据，如netperf

#### netperf
主要针对基于TCP或UDP的传输。Netperf根据应用不同，可以进行不同模式的网络性能测试，即批量数据传输（bulk data transfer)模式和请求/应答模式。Netperf测试结果  
反映的是一个系统能够以多快速度向另一个系统发送数据，一级另外一个系统能够以多快的速度接受数据。  

Netperf工具以client/server方式工作。server端是netserver，用来侦听来自client端的连接，client端是netperf，用来向server发起网络测试。在client与server之间，  
首先建立一个控制连接，传递有关测试配置的信息，以及测试的结果；在控制连接建立并传递了测试配置信息以后，client与server之间会再建立一个测试连接，  
用来来回传递着特殊的流量模式，以测试网络的性能。  

#### TCP网络性能
由于TCP协议能够提供端到端的可靠传输，因此被大量的网络应用程序使用。但是，可靠性的建立是要付出代价的。TCP协议保证可靠性的措施，如建立并维护连接、控制数据有序的传递等都会消耗一定的网络带宽。   
Netperf可以模拟三种不同的TCP流量模式：    
- 单个TCP连接，批量（bulk）传输大量数据    
- 单个TCP连接，client请求/server应答的交易（transaction）方式    
- 多个TCP连接，每个连接中一对请求/应答的交易方式    

#### UDP网络性能  
UDP没有建立连接的负担，但是UDP不能保证传输的可靠性，所以使用UDP的应用程序需要自行跟踪每个发出的分组，并重发丢失的分组。    
Netperf可以模拟两种UDP的流量模式：    
- 从client到server的单向批量传输   
- 请求/应答的交易方式  

由于UDP传输的不可靠性，在使用netperf时要确保发送的缓冲区大小不大于接收缓冲区大小，否则数据会丢失，    
netperf将给出错误的结果。因此，对于接收到分组的统计不一定准确，需要结合发送分组的统计综合得出结论。    

测试批量（bulk）网络流量的性能  

批量数据传输典型的例子有ftp和其它类似的网络应用（即一次传输整个文件）。根据使用传输协议的不同，批量数据传输又分为TCP批量传输和UDP批量传输。  

1．	TCP_STREAM

Netperf缺省情况下进行TCP批量传输，即-t TCP_STREAM。测试过程中，netperf向netserver发送批量的TCP数据分组，以确定数据传输过程中的吞吐量：  

```C++
./netperf -H 192.168.0.28 -l 60
TCP STREAM TEST to 192.168.0.28
Recv   Send    Send
Socket Socket  Message  Elapsed
Size   Size    Size     Time     Throughput
bytes  bytes   bytes    secs.    10^6bits/sec
  
 87380  16384  16384    60.00      88.00
 ```    
从netperf的结果输出中，我们可以知道以下的一些信息：  

1）	远端系统（即server）使用大小为87380字节的socket接收缓冲  

2）	本地系统（即client）使用大小为16384字节的socket发送缓冲  

3）	向远端系统发送的测试分组大小为16384字节  

4）	测试经历的时间为60秒  

5）	吞吐量的测试结果为88Mbits/秒  

在缺省情况下，netperf向发送的测试分组大小设置为本地系统所使用的socket发送缓冲大小。  

TCP_STREAM方式下与测试相关的局部参数如下表所示：  

参数	说明  
-s size	设置本地系统的socket发送与接收缓冲大小  
-S size	设置远端系统的socket发送与接收缓冲大小  
-m size	设置本地系统发送测试分组的大小  
-M size	设置远端系统接收测试分组的大小  
-D	对本地与远端系统的socket设置TCP_NODELAY选项  
通过修改以上的参数，并观察结果的变化，我们可以确定是什么因素影响了连接的吞吐量。例如，如果怀疑路由器由于缺乏足够的缓冲区空间，使得转发大的分组时存在问题，就可以增加测试分组（-m）的大小，以观察吞吐量的变化：  

```C++
./netperf -H 192.168.0.28 -l 60 -- -m 2048
TCP STREAM TEST to 192.168.0.28
Recv   Send    Send
Socket Socket  Message  Elapsed
Size   Size    Size     Time     Throughput
bytes  bytes   bytes    secs.    10^6bits/sec
  
 87380  16384   2048    60.00      87.62
```
在这里，测试分组的大小减少到2048字节，而吞吐量却没有很大的变化（与前面例子中测试分组大小为16K字节相比）。相反，如果吞吐量有了较大的提升，则说明在网络中间的路由器确实存在缓冲区的问题。  

2．	UDP_STREAM  
UDP_STREAM用来测试进行UDP批量传输时的网络性能。需要特别注意的是，此时测试分组的大小不得大于socket的发送与接收缓冲大小，否则netperf会报出错提示：  

```C++
./netperf -t UDP_STREAM -H 192.168.0.28 -l 60
UDP UNIDIRECTIONAL SEND TEST to 192.168.0.28
udp_send: data send error: Message too long
```
为了避免这样的情况，可以通过命令行参数限定测试分组的大小，或者增加socket的发送/接收缓冲大小。UDP_STREAM方式使用与TCP_STREAM方式相同的局部命令行参数，因此，这里可以使用-m来修改测试中使用分组的大小：  

```C++
./netperf -t UDP_STREAM -H 192.168.0.28 -- -m 1024
UDP UNIDIRECTIONAL SEND TEST to 192.168.0.28
Socket  Message  Elapsed      Messages
Size    Size     Time         Okay Errors   Throughput
bytes   bytes    secs            #      #   10^6bits/sec
  
 65535    1024   9.99       114127      0      93.55
 65535           9.99       114122             93.54
```
UDP_STREAM方式的结果中有两行测试数据，第一行显示的是本地系统的发送统计，这里的吞吐量表示netperf向本地socket发送分组的能力。  
但是，我们知道，UDP是不可靠的传输协议，发送出去的分组数量不一定等于接收到的分组数量。  

第二行显示的就是远端系统接收的情况，由于client与server直接连接在一起，而且网络中没有其它的流量，所以本地系统发送过去的分组几乎都被远端系统正确的接收了，远端系统的吞吐量也几乎等于本地系统的发送吞吐量。  
但是，在实际环境中，一般远端系统的socket缓冲大小不同于本地系统的socket缓冲区大小，而且由于UDP协议的不可靠性，远端系统的接收吞吐量要远远小于发送出去的吞吐量。  
 
测试请求/应答（request/response）网络流量的性能

另一类常见的网络流量类型是应用在client/server结构中的request/response模式。  
每次交易（transaction）中，client向server发出小的查询分组，server接收到请求，经处理后返回大的结果数据。如下图所示：  


1．	TCP_RR

TCP_RR方式的测试对象是多次TCP request和response的交易过程，但是它们发生在同一个TCP连接中，这种模式常常出现在数据库应用中。  
数据库的client程序与server程序建立一个TCP连接以后，就在这个连接中传送数据库的多次交易过程。  

```C++
./netperf -t TCP_RR -H 192.168.0.28
TCP REQUEST/RESPONSE TEST to 192.168.0.28
Local /Remote
Socket Size   Request  Resp.   Elapsed  Trans.
Send   Recv   Size     Size    Time     Rate
bytes  Bytes  bytes    bytes   secs.    per sec
  
16384  87380  1        1       10.00    9502.73
16384  87380
```
Netperf输出的结果也是由两行组成。第一行显示本地系统的情况，第二行显示的是远端系统的信息。平均的交易率（transaction rate）为9502.73次/秒。  
注意到这里每次交易中的request和response分组的大小都为1个字节，不具有很大的实际意义。用户可以通过测试相关的参数来改变request和response分组的大小，TCP_RR方式下的参数如下表所示：  

参数	说明  
-r req,resp	设置request和reponse分组的大小  
-s size	设置本地系统的socket发送与接收缓冲大小  
-S size	设置远端系统的socket发送与接收缓冲大小  
-D	对本地与远端系统的socket设置TCP_NODELAY选项  
通过使用-r参数，我们可以进行更有实际意义的测试：  

```C++
./netperf -t TCP_RR -H 192.168.0.28 -- -r 32,1024
TCP REQUEST/RESPONSE TEST to 192.168.0.28
Local /Remote
Socket Size   Request  Resp.   Elapsed  Trans.
Send   Recv   Size     Size    Time     Rate
bytes  Bytes  bytes    bytes   secs.    per sec
  
16384  87380  32       1024    10.00    4945.97
16384  87380
```
从结果中可以看出，由于request/reponse分组的大小增加了，导致了交易率明显的下降。 注：相对于实际的系统，这里交易率的计算没有充分考虑到交易过程中的应用程序处理时延，因此结果往往会高于实际情况。  

2．	TCP_CRR

与TCP_RR不同，TCP_CRR为每次交易建立一个新的TCP连接。最典型的应用就是HTTP，每次HTTP交易是在一条单独的TCP连接中进行的。因此，由于需要不停地建立新的TCP连接，并且在交易结束后拆除TCP连接，交易率一定会受到很大的影响。  

```C++
./netperf -t TCP_CRR -H 192.168.0.28 
TCP Connect/Request/Response TEST to 192.168.0.28
Local /Remote
Socket Size   Request  Resp.   Elapsed  Trans.
Send   Recv   Size     Size    Time     Rate
bytes  Bytes  bytes    bytes   secs.    per sec
  
131070 131070 1        1       9.99     2662.20
16384  87380
```
即使是使用一个字节的request/response分组，交易率也明显的降低了，只有2662.20次/秒。TCP_CRR使用与TCP_RR相同的局部参数。  

3．	UDP_RR

UDP_RR方式使用UDP分组进行request/response的交易过程。由于没有TCP连接所带来的负担，所以我们推测交易率一定会有相应的提升。  

```C++
./netperf -t UDP_RR -H 192.168.0.28 
UDP REQUEST/RESPONSE TEST to 192.168.0.28
Local /Remote
Socket Size   Request  Resp.   Elapsed  Trans.
Send   Recv   Size     Size    Time     Rate
bytes  Bytes  bytes    bytes   secs.    per sec
  
65535  65535  1        1       9.99     10141.16
65535  65535
```
结果证实了我们的推测，交易率为10141.16次/秒，高过TCP_RR的数值。不过，如果出现了相反的结果，即交易率反而降低了，也不需要担心，因为这说明了在网络中，路由器或其它的网络设备对UDP采用了与TCP不同的缓冲区空间和处理技术。  



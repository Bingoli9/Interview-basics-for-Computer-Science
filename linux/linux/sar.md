## sar

### 内存使用情况统计

-r: 输出物理内存和虚拟内存的统计信息
```C++
[root@obe11g ~]# sar -r 5 4  
  
05:11:21 AM kbmemfree kbmemused  %memused kbbuffers  kbcached kbswpfree kbswpused  %swpused  kbswpcad  
05:11:26 AM    291880   1645960     84.94     47836   1309352   4192956         0      0.00         0  
05:11:31 AM    291832   1646008     84.94     47836   1309352   4192956         0      0.00         0  
05:11:36 AM    291816   1646024     84.94     47836   1309352   4192956         0      0.00         0  
05:11:41 AM    293608   1644232     84.85     47836   1309372   4192956         0      0.00         0  
Average:       292284   1645556     84.92     47836   1309357   4192956         0      0.00         0  
  
参数解释：  
  
kbmemfree：剩余可用内存、单位K  
kbmemused：已用内存、以K 为单位、该值不考虑内核自身所使用的内存  
%memused：已用内存百分比  
kbbuffers：已用buffer(内核所用)、单位K  
kbcached：已用cache（内核所用）、单位K  
kbswpfree：剩余Swap、单位K  
kbswpused：已用Swap、单位K  
%swpused：已用Swap百分比  
kbswpcad：被缓存的Swap、单位K  
```

### 分页统计
```C++
05:16:56 AM  pgpgin/s pgpgout/s   fault/s  majflt/s  
05:17:01 AM      0.00     39.20      4.60      0.00  
05:17:06 AM      0.00     23.20    117.20      0.00  
05:17:11 AM      0.00     23.20    114.00      0.00  
05:17:16 AM      0.00     14.40    113.80      0.00  
05:17:21 AM      0.80     48.00   1470.00      0.00  
Average:         0.16     29.60    363.92      0.00  
  
参数解释：  
  
pgpgin/s：表示每秒从磁盘或SWAP置换到内存的字节数(KB)  
pgpgout/s：表示每秒从内存置换到磁盘或SWAP的字节数(KB)  
fault/s：每秒钟系统产生的缺页数,即主缺页与次缺页之和(major + minor)  
majflt/s：每秒钟产生的主缺页数.  
```

### CPU
```C++
05:25:41 AM       CPU     %user     %nice   %system   %iowait     %idle  
05:25:44 AM       all      2.00      0.00      1.67      0.00     96.33  
05:25:47 AM       all      0.67      0.00      1.00      0.00     98.33  
05:25:50 AM       all      2.00      0.00      1.00      0.00     97.00  
05:25:53 AM       all      4.00      0.00      6.33      0.00     89.67  
05:25:56 AM       all      0.67      0.00      1.67      0.00     97.67  
Average:          all      1.87      0.00      2.33      0.00     95.80  
  
参数解释：  
  
%user：显示在用户级别(application)运行使用 CPU 总时间的百分比  
%nice：显示在用户级别，用于nice操作，所占用 CPU 总时间的百分比  
%system：在核心级别(kernel)运行所使用 CPU 总时间的百分比  
%iowait：显示用于等待I/O操作占用 CPU 总时间的百分比  
%idle：显示 CPU 空闲时间占用 CPU 总时间的百分比  
```

以下是三种常见的场景：
   1）若 %iowait 的值过高，表示硬盘存在I/O瓶颈
   2）若 %idle 的值高但系统响应慢时，有可能是 CPU 等待分配内存，此时应加大内存容量
   3）若 %idle 的值持续低于1，则系统的 CPU 处理能力相对较低，表明系统中最需要解决的资源是 CPU

### IO

- 磁盘IO
```C++
05:32:02 AM       tps      rtps      wtps   bread/s   bwrtn/s  
05:32:05 AM      0.00      0.00      0.00      0.00      0.00  
05:32:08 AM      0.00      0.00      0.00      0.00      0.00  
05:32:11 AM      0.00      0.00      0.00      0.00      0.00  
05:32:14 AM      0.00      0.00      0.00      0.00      0.00  
05:32:17 AM      0.00      0.00      0.00      0.00      0.00  
Average:         0.00      0.00      0.00      0.00      0.00  
  
参数解释：  
  
tps：每秒磁盘的 I/O 传输总量  
rtps：每秒从磁盘读出的数据总量  
wtps：每秒向磁盘写入的数据总量  
bread/s：每秒从磁盘读出的数据量，单位为 块/s  
bwrtn/s：每秒向磁盘写入的数据量，单位为 块/s  
```

- 网络IO
  用法sar -n { keyword [,...] | ALL }, keyword包括：
   DEV, EDEV, NFS, NFSD, SOCK, IP, EIP, ICMP, EICMP, TCP, ETCP, UDP, SOCK6, IP6, EIP6, ICMP6, EICMP6 和 UDP6
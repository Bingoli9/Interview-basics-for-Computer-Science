## TCP Optimize

| 优化方法                                              | 内核选项                                                     | 参考设置    |
| ----------------------------------------------------- | ------------------------------------------------------------ | ----------- |
| 增大处于time_wait状态的连接的数量                     | net.ipv4.tcp_max_tw_buckets                                  | 1048576     |
| 增大连接跟踪表的大小                                  | net.netfilter.nf_conntrack_max                               | 1048576     |
| 缩短处于time_wait状态连接的超时时间                   | net.ipv4.tcp_fin_timeout                                     | 15          |
| 缩短连接跟踪表中处于time_wait状态连接的超时时间       | net.netfilter.nf_conntrack_tcp_timeout_time_wait             | 30          |
| 允许time_wait状态连接占用的端口还可以用到新建的连接中 | net.ipv4.tcp_tw_reuse                                        | 1           |
| 增大本地端口号的范围                                  | net.ipv4.ip_local_port_range                                 | 10000 65000 |
| 增加系统和应用程序的最大文件描述符数                  | fs.nr_open（系统），systemd配置文件中的LimitNOFIL（应用程序） | 1048576     |
| 增加半连接的最大数量                                  | net.ipv4.tcp_max_syn_backlog                                 | 16384       |
| 开启SYN Cookies                                       | net.ipv4.tcp_syncookies                                      | 1           |
| 缩短发送keepalive探测包的间隔时间                     | net.ipv4.tcp_keepalive_intvl                                 | 30          |
| 减少keepalive探测失败后通知应用程序前的重试次数       | net.ipv4.tcp_keepalive_probes                                | 3           |
| 缩短最后一次数据包到keepalive探测包的间隔时间         | net.ipv4.tcp_keepalive_time                                  | 600         |



#### tcp fast open

浏览器和服务单需同时支持。


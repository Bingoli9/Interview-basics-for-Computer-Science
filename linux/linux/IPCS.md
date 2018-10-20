## IPCS

ipcs是linux下显示进程间通信设施状态的工具。可以显示消息队列、共享内存和信号量信息。

### IPCS资源查询

ipcs -m 查看系统使用的IPC共享内存资源

ipcs -q 查看系统使用的IPC队列资源

ipcs -s 查看系统使用的IPC信号资源

### 系统IPC参数查询

ipcs -l

### 运用

查询user1用户环境上是否存在积Queue现象

1. 查询队列Queue

2. 找出第6列大于0的服务

   ```
   ipcs -q |grep user1 | awk '{if($5>0) print $0}'
   ```

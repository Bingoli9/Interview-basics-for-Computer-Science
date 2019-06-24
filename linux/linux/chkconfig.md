## chkconfig命令


1.chkconfig是一个改变开机启动项的命令，修改/etc/rc[0-6].d文件夹下的内容

2.chkconfig命令有5种不同的作用：增加新的服务、删除服务、打印当前开启启动服务的信息、修改开启启动服务的信息、检查一个指定服务的状态

3.当chkconfig servicename时，它检查这个服务是不是在当前的runlevel下被开启启动，如果是，返回true,否则false。chkconfig --level= servicename检查服务是不是在指定的runlevel开机启动

4.当chkconfig --list时，或者完全没有参数即chkconfig时，会列出当前的服务和他们的配置

5.如果on、off、reset、resetpriorities参数之一被指定时(在服务名参数后面)，chkconfig命名改变这个服务的开机配置。on/off使服务开机启动/停止。reset标志重置on/off不论在开机启动脚本中是什么样子的，resetpriorities也是，只是有优先级

6.默认，on/off命令支队runlevel为2,3,4,5的有影响，而reset和resetpriorities对所有runlevels都有影响。--level参数可以指定被影响的runlevel

7.对每个服务，每个runlevel都有1个start/stop脚本。当change runlevel时，init进程不会重启一个already-start的服务，也不会重新关闭一个already-stop的服务


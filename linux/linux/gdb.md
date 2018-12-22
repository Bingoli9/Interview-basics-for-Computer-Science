## gdb

- 调试已经运行的进程

gdb program processID  
或者  
先启动gdb,然后用“attach”命令附着在进程上  
attach processID  

- 在匿名空间设置断点
在gdb中，如果要对namespace Foo中的foo函数设置断点，可以使用如下命令：  
(gdb) b Foo::foo  


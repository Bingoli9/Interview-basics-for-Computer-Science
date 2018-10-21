## ipcrm
ipcrm用于移除一个消息对象，或者共享内存段，或者一个信号集，同时会将与ipc对象相关链的数据也一并移除。

## ipcrm用法
```c++
	ipcrm -M shmkey 移除用shmkey创建的共享内存段
	ipcrm -m shmid 移除用shmkey标识的共享内存段
	ipcrm -Q msqkey 移除用msqkey创建的消息队列
	ipcrm -q msqid 移除用msqid标识的消息队列
	ipcrm -S semkey 移除用semkey创建的信号
	ipcrm -s semid 移除用semid标识的信号
```
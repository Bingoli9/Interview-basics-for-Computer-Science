## Linux内核调度策略
- SCHED_FIFO
    first in first out 实时调度策略
- SCHED_RR
    robin round 实时调度策略
- SCHED_DEADLINE
    基于Earliest Deadline First (EDF) 调度算法
- SCHED_OTHER
    分时调度策略
- SCHED_BATCH
    批处理
- SCHED_IDLE
    优先级最低的策略

SCHED_DEADLINE是新支持的实时进程调度策略，针对突发型计算，且适用于延迟和完成时间高度敏感的任务   

SCHED_OTHER策略是普通进程的默认调度策略。 SCHED_OTHER调度策略首先根据进程的nice值确定分配CPU的执行时间。若进程没有等待资源则进程变为就绪状态。  
然后调度程序遍历就绪队列中的进程，计算每个进程的动态优先级(counter+20-nice)，并挑选动态优先级最高的进程去运行，直到时间片用完或主动放弃CPU。  




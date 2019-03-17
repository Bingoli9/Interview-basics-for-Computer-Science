## CPU Affinity

CPU affinity can be divided into two categories: soft affinity and hard affinity.

The Linux kernel process scheduler inherently has a feature called CPU soft affinity, which means that processes typically do not migrate frequently between processors.This is exactly what we want, because less frequent process migration means less load generation.But that doesn't mean there won't be a small migration.

CPU hard affinity refers to the CPU affinity setting interface provided by Linux, which indicates that a certain process is running on a certain processor.

CPU affinity can prevent OS from **core migration**. In SMP architecture, each CPU has its own cache. If core migration happen, it will cause cache miss and degrade the program performance significantly.

```C++

#define _GNU_SOURCE             
#include <sched.h>
 
int sched_setaffinity(pid_t pid, size_t cpusetsize,cpu_set_t *mask);    //设定pid 绑定的cpu， 
int sched_getaffinity(pid_t pid, size_t cpusetsize,cpu_set_t *mask);    //查看pid 绑定的cpu。
```

```C++
cpu_set_t  //是一个掩码数组，一共有1024位，每一位都可以对应一个cpu核心
//以下宏，都是对这个掩码进行操作的。如果需要，一个进程是可以绑定多个cpu的。
void CPU_ZERO(cpu_set_t *set);
void CPU_SET(int cpu, cpu_set_t *set);
void CPU_CLR(int cpu, cpu_set_t *set);
int CPU_ISSET(int cpu, cpu_set_t *set);
```


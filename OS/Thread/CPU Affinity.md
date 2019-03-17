## CPU Affinity

CPU affinity can be divided into two categories: soft affinity and hard affinity.

The Linux kernel process scheduler inherently has a feature called CPU soft affinity, which means that processes typically do not migrate frequently between processors.This is exactly what we want, because less frequent process migration means less load generation.But that doesn't mean there won't be a small migration.

CPU hard affinity refers to the CPU affinity setting interface provided by Linux, which indicates that a certain process is running on a certain processor.

CPU affinity can prevent OS from **core migration**. In SMP architecture, each CPU has its own cache. If core migration happen, it will cause cache miss and degrade the program performance significantly.

### Processor CPU Affinity

```C++

#define _GNU_SOURCE             
#include <sched.h>
 
int sched_setaffinity(pid_t pid, size_t cpusetsize,cpu_set_t *mask);    //设定pid 绑定的cpu， 
int sched_getaffinity(pid_t pid, size_t cpusetsize,cpu_set_t *mask);    //查看pid 绑定的cpu。
```

```C++
void CPU_ZERO (cpu_set_t *set)
/*这个宏对 CPU 集 set 进行初始化，将其设置为空集。*/
void CPU_SET (int cpu, cpu_set_t *set)
/*这个宏将 指定的 cpu 加入 CPU 集 set 中*/
void CPU_CLR (int cpu, cpu_set_t *set)
/*这个宏将 指定的 cpu 从 CPU 集 set 中删除。*/
int CPU_ISSET (int cpu, const cpu_set_t *set)
/*如果 cpu 是 CPU 集 set 的一员，这个宏就返回一个非零值（true），否则就返回零（false）。*/
```

example

```C++
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/* sysconf( _SC_NPROCESSORS_CONF ) 查看cpu的个数；打印用%ld长整。
 * sysconf( _SC_NPROCESSORS_ONLN ) 查看在使用的cpu个数；打印用%ld长整 */
int main(int argc, char **argv)
{
    int cpus = 0;
    int  i = 0;
    cpu_set_t mask;
    cpu_set_t get;

    cpus = sysconf(_SC_NPROCESSORS_CONF);
    printf("cpus: %d\n", cpus);

    CPU_ZERO(&mask);    /* 初始化set集，将set置为空*/
    CPU_SET(0, &mask);  /* 依次将0、1、2、3号cpu加入到集合，前提是你的机器是多核处理器*/
    CPU_SET(1, &mask);
    CPU_SET(2, &mask);
    CPU_SET(3, &mask);
    
    /*设置cpu 亲和性（affinity）*/
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
        printf("Set CPU affinity failue, ERROR:%s\n", strerror(errno));
        return -1; 
    }   
    usleep(1000); /* 让当前的设置有足够时间生效*/

    /*查看当前进程的cpu 亲和性*/
    CPU_ZERO(&get);
    if (sched_getaffinity(0, sizeof(get), &get) == -1) {
        printf("get CPU affinity failue, ERROR:%s\n", strerror(errno));
        return -1; 
    }   
    
    /*查看运行在当前进程的cpu*/
    for(i = 0; i < cpus; i++) {

        if (CPU_ISSET(i, &get)) { /*查看cpu i 是否在get 集合当中*/
            printf("this process %d of running processor: %d\n", getpid(), i); 
        }    
    }
    sleep(3); //让程序停在这儿，方便top命令查看
       
    return 0;
}
```

result:

```C++
[root@localhost test]# ./test    
cpus: 24
this process 2848 of running processor: 0
this process 2848 of running processor: 1
this process 2848 of running processor: 2
this process 2848 of running processor: 3
```

### Thread CPU Affinity

```C++
NAME
       pthread_setaffinity_np, pthread_getaffinity_np - set/get CPU affinity of a thread

SYNOPSIS
       #define _GNU_SOURCE             /* See feature_test_macros(7) */
       #include <pthread.h>

       int pthread_setaffinity_np(pthread_t thread, size_t cpusetsize,
                                  const cpu_set_t *cpuset);
       int pthread_getaffinity_np(pthread_t thread, size_t cpusetsize,
                                  cpu_set_t *cpuset);

       Compile and link with -pthread.

DESCRIPTION
       The  pthread_setaffinity_np()  function  sets the CPU affinity mask of the thread thread to the CPU set pointed to by cpuset.  If the call is successful, and the thread is not
       currently running on one of the CPUs in cpuset, then it is migrated to one of those CPUs.

       The pthread_getaffinity_np() function returns the CPU affinity mask of the thread thread in the buffer pointed to by cpuset.

       For more details on CPU affinity masks, see sched_setaffinity(2).  For a description of a set of macros that can be used to manipulate and inspect CPU sets, see CPU_SET(3).

       The argument cpusetsize is the length (in bytes) of the buffer pointed to by cpuset.  Typically, this argument would be specified as sizeof(cpu_set_t).  (It may be some  other
       value, if using the macros described in CPU_SET(3) for dynamically allocating a CPU set.)

RETURN VALUE
       On success, these functions return 0; on error, they return a nonzero error number
```

example:

```C++
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

void *testfunc(void *arg)
{
    int i, cpus = 0;
    cpu_set_t mask;
    cpu_set_t get;

    cpus = sysconf(_SC_NPROCESSORS_CONF);
    printf("this system has %d processor(s)\n", cpus);
    
    CPU_ZERO(&mask);
    for (i = 0; i < 4; i++) { /*将0、1、2、3添加到集合中*/
        CPU_SET(i, &mask);
    }   

    /* 设置cpu 亲和性(affinity)*/
    if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {
        fprintf(stderr, "set thread affinity failed\n");
    }   
    
    /* 查看cpu 亲和性(affinity)*/
    CPU_ZERO(&get);
    if (pthread_getaffinity_np(pthread_self(), sizeof(get), &get) < 0) {
        fprintf(stderr, "get thread affinity failed\n");
    }   

    /* 查看当前线程所运行的所有cpu*/
    for (i = 0; i < cpus; i++) {
        if (CPU_ISSET(i, &get)) {
            printf("this thread %d is running in processor %d\n", (int)pthread_self(), i); 
        }   
    }   
    sleep(3); //查看
    
    pthread_exit(NULL);
}
 
int main(int argc, char *argv[])
{
    pthread_t tid;
    if (pthread_create(&tid, NULL, (void *)testfunc, NULL) != 0) {
        fprintf(stderr, "thread create failed\n");
        return -1; 
    }   

    pthread_join(tid, NULL);
    return 0;
}
```

```C++
[root@localhost thread]# ./test                      
this system has 24 processor(s)
this thread 2812323584 is running in processor 0
this thread 2812323584 is running in processor 1
this thread 2812323584 is running in processor 2
this thread 2812323584 is running in processor 3
```


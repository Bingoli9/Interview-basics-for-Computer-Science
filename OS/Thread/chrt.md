## chrt

### 查看进程的调度策略及优先级　　

```C++
chrt -p $pid
```


### 查看每种策略的有效优先级范围

```C++
chrt -m

```


```C++
SCHED_OTHER 最小/最大优先级    : 0/0
SCHED_FIFO 最小/最大优先级     : 1/99
SCHED_RR 最小/最大优先级       : 1/99
SCHED_BATCH 最小/最大优先级    : 0/0
SCHED_IDLE 最小/最大优先级     : 0/0
SCHED_DEADLINE 最小/最大优先级 : 0/0
```


### 设置进程的调度策略
```C++
chrt [-b/-f/-o/-r/-i/-d] -p [$priority] $pid
```


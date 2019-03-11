## gdb dead lock

```C++
gdb
attach pid
thread applay all bt
```

Then look at the stack information of all the threads, find out the two threads that meet the deadlock criteria, and find out the exact location of the deadlock.




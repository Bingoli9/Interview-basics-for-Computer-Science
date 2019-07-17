## Object

Mainly talking about `wait`, `notify`

我们可以用Object超类来声明lock 对象，Object对象声明了：  
- wait
- notify
- notifyAll


lock对象，线程A，线程B关系：  

- lock对象维护list队列
- 线程A中执行lock的wait方法，把线程A保存到list中
- 线程B中执行lock的notify方法，把线程A从list唤醒

### wait
```c++
This method causes the current thread to place itself in the wait set for this object 
and then to relinquish any and all synchronizon claims on this object
```


### notify
```C++
Wakes up all threads that are waiting on this object's monitor
```












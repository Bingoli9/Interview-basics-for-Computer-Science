## TLS
TLS:线程局部存储  
如果希望某全局变量只能在一个线程内的所有方法访问, 但其他线程无法访问,需要实现TLS机制  

TLS在每个平台上有不同的实现, 可移植性不太好  


### TLS简单实现方式  
```C++
全局hash表, key为每个tid
```

### TLS在linux平台的实现方式  
```C++
int pthread_key_create(pthread_key_t *key, void (*destructor)(void*));
int pthread_key_delete(pthread_key_t key);
void *pthread_getspecific(pthread_key_t key);
int pthread_setspecific(pthread_key_t key, const void *value);
```

### 局限
每个TLS槽都由一个唯一的键值（key）标识，这个键值由进程负责向OS申请分配，  
如果当前进程申请的键值数量超过系统规定的上限，申请将失败，即无法获取一  
个新的TLS槽。在Android系统中，将导致app崩溃  

### chromium android os
针对上述局限, chromium自己独立管理TLS  

允许每个线程申请TLS key并且同一个key 绑定不同类型的数据, 从而解决TLS key不够用的问题  









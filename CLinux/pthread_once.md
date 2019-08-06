## pthread_once

#### 头文件
#include <pthread.h>

#### 语法
```C++
int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));
pthread_once_t once_control = PTHREAD_ONCE_INIT; 
```

#### 描述
如果once_control赋值为PTHREAD_ONCE_INIT, 那么指针函数init_routine只会被调用一次, 后续  
其他线程的调用都不会调用init_routine






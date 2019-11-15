## chromium stack info

```
gn args out/component

```


#### c 层调用堆栈

```C++
C层调用堆栈：
#include "base/debug/stack_trace.h"
base::debug::StackTrace().Print();
```

#### java调用堆栈

```C++
Java层调用栈：
Log.d(TAG,Log.getStackTraceString(new Throwable()));
```


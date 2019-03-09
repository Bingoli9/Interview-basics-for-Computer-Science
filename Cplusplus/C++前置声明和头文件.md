## C++前置声明和头文件

假设有一个Date类

Date.h

```c++
class Date {
private:
	int year, month, day;
};
```

如果有个Task类的定义要用到Date类，有两种写法

其一

Task1.h

```c++
class Date;
class Task1 {
public:
	Date getData();
};
```

其二

Task2.h

```c++
#include "Date.h"
class Task2 {
public:
	Date getData();
};
```

一个采用前置声明，一个采用#include<Date.h>加入了Date的定义。两种方法都能通过编译。但是 Task1.h 这种写法更好。如果Date.h 的 private 成员变量改变，比如变成 double year, month, day; ，Task1.h 不需要重新编译，而 Task2.h 就要重新编译，更糟的是如果 Task2.h 还与其他很多头文件有依赖关系，就会引发一连串的重新编译，花费极大的时间。可是事实上改变一下写法就可以省去很多功夫。

所以**能用前置声明代替#include 的时候，尽量用前置声明**

有些情况不能用前置声明代替#include

比如Task1.h改成

```c++
class Date;
class Task1 {
public:
	Date d;
};
```

会编译错误，因为Date d定义了一个Date类型变量，编译器为d分配内存空间的时候必须知道d的大小，必须包含定义Date类的Date.h文件。

这是可以采用指针来代替

```c++
class Date;
class Task1 {
public:
	Date *d;
};
```

指针的大小是固定的。在32位机上是4字节，64位机上是8字节。这时编译Task1的时候不需要Date的大小，所以和Date的定义无关。

何时可以用前置声明代替#include

**如果使用object reference 或 object point 可以完成任务，就不要用object**

这样可以尽最大可能避免#include



**为声明式和定义是提供不同的头文件** 

在函数库的设计过程中，接口的设计就要遵循上述准则。

一个接口的头文件是这样的

interface.h

```c++
class Date;
class Address;
class Email;
Date getDate();
```

如果客户只用到Date类，编译器就只会去编译Date.h，而不去编译Address.h，Email.h 等等文件。

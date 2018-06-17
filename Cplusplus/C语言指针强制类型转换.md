### C语言指针强制类型转换

指针作为一个变量，占据一个4字节的地址空间（由于程序的寻址空间是2^32次方，即4GB，所以用4个字节表示指针就已经能指向任何程序能够寻址到的空间了，所以指针的大小为4字节。

指针to指针的强制类型转换是指将指针所指的内容的类型由原先的类型转换为后面的类型。

```c
int a = 1;

int *p = &a;

float *p1 = (float*)p;

```

则p和p1的值都是&a，但是*p是将&a地址中的值按照int型变量进行解释，而*p1则是将&a地址中的值按照float型变量进行解释。

### 1、指针类型强制转换

```c++
int m;

int *pm = &m;

char *cp = (char *)&m;
```

### 2、结构体之间的强制转换

```c++
struct str1 a;

struct str2 b;

a=(struct str1) b;                   //this is wrong

a=*((struct str1*)&b);              //this is correct

```


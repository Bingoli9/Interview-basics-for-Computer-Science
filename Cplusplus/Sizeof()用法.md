# Sizeof()用法

sizeof()的功能：计算数据空间的字节数。

1、与strlen()比较：

​	strlen()计算字符数组的字符数，以"\0"为结束判断不计算"\0"的数组元素。

​	sizeof()计算数据所占用的空间，用字节数表示。

2、指针与静态数组的sizeof的操作。

​	指针均可看为变量类型的一种。所有指针变量的sizeof操作结果均为4.	

​        注意：int  *p; sizeof(p) = 4; 但sizeof( *p)相当与sizeof(int)；

​        对于静态数组，sizeof可直接计算数组大小；

​	例：int a[10]; char b[]="hello";

​	sizeof(a)等于4*10=40；

​	sizeof(b)等于6；

3、sizeof字符串的注意

​	string s="hello";

​	sizeof(s)等于string类的大小，sizeof(s.cstr())得到的是与字符串的长度。

4、union与struct的空间计算。

​	遵循两个原则：

​	（1）整体空间是占用空间最大成员所占字节数的整倍数。

​	（2）数据对齐原则：内存按结构成员的先后顺序排列，当排到该成员变量时，其前面已摆放的空间大小必须是该成员类型大小的整倍数，如果不够则补齐。

5、在64位各个类型占用空间：

char： 1

int：4

long： 8

short： 2

long int: 8

long long: 8

long long int: 8

float: 4

double: 8

long double: 16

指针: 8

6、在32为各个类型占用空间：

char: 1

int: 4

short: 2

long: 4

long  int: 4

long long: 8

float: 4

double: 8

long double: 8

指针： 4




## sizeof

- sizeof是运算符，不是函数
- sizeof不能求得void类型长度
- sizeof能求得void类型指针长度
- sizeof能求得静态分配内存的数组的长度
- sizeof不能求得动态分配的内存大小
- sizeof不能对不完整数组求长度
- 当表达式作为sizeof的操作数时，它返回表达式的计算结果类型大小，但是不对表达式求值
- sizeof不能用于求结构体位域成员大小，但是可以求得包含位域成员结构大小
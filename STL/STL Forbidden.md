## STL Forbidden 

#### 代码膨胀

模板使用问题和异常使用

#### 内存使用效率问题

std::string sizeof是28. 因为内置16字节数组来做小字符串优化。低于16字节的字符串都会占用28字节内存。

map内存分配问题

#### deep copy

传递参数用const 引用，赋值用swap代替


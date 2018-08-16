## c++11 std::bind

用来将可调用对象与其参数 一起进行绑定。绑定后可以使用std::function来进行保存，并延迟到我们需要的时候调用。

（1） 将可调用对象与其参数绑定成一个仿函数；

（2） 可绑定部分参数。

在绑定部分参数的时候，通过使用std::placeholders来决定空位参数将会是调用发生时的第几个参数。

```c++
#include "stdafx.h"
#include<iostream>// std::cout
#include<functional>// std::function

class A
{
public:
    int i_ = 0; // C++11允许非静态（non-static）数据成员在其声明处（在其所属类内部）进行初始化

    void output(int x, int y)
    {
        std::cout << x << "" << y << std::endl;
    }

};

int main()
{
    A a;
    // 绑定成员函数，保存为仿函数
    std::function<void(int, int)> fr = std::bind(&A::output, &a, std::placeholders::_1, std::placeholders::_2);
    // 调用成员函数
    fr(1, 2);

    // 绑定成员变量
    std::function<int&(void)> fr2 = std::bind(&A::i_, &a);
    fr2() = 100;// 对成员变量进行赋值
    std::cout << a.i_ << std::endl;


    return 0;
}
```


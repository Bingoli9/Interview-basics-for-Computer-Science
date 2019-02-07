## closure

The function closure is the function with context, that is, the closure function has state. 

**Function is code, state is variable, bind the code and state, it's closure**

### Implement ation

#### Functor

overload **operator()**

```C++
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>


class MyFunctor
{
public:
    MyFunctor(int temp): round(temp) {}
    int operator()(int temp) {return temp + round; }
private:
    int round;
};


void mytest()
{
    int round = 2;
    MyFunctor f(round);
    std::cout << "result: " << f(1) << std::endl; // operator()(int temp)

    return;
}

int main()
{
    mytest();

    system("pause");
    return 0;
}
```

#### std::bind 

```C++
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <vector>
#include <map>

void func(void)
{// 普通全局函数
    std::cout << __FUNCTION__ << std::endl;
}

class Foo
{
public:
    static int foo_func(int a)
    {// 类中的静态函数
        std::cout << __FUNCTION__ << "(" << a << ")->: ";
        return a;
    }
};

class Bar
{
public:
    int operator ()(int a)
    {// 仿函数
        std::cout << __FUNCTION__ << "(" << a << ")->: ";
        return a;
    }
};

void mytest()
{
    // std::function对象最大的用处就是在实现函数回调，使用者需要注意，它不能被用来检查相等或者不相等，但是可以与NULL或者nullptr进行比较。

    // 绑定一个普通函数
    std::function< void(void) > f1 = func;
    f1();

    // 绑定类中的静态函数
    std::function<int(int)> f2 = Foo::foo_func;
    std::cout << f2(11) << std::endl;

    // 绑定一个仿函数
    Bar obj;
    std::function<int(int)> f3 = obj;
    std::cout << f3(222) << std::endl;

    /*
     运行结果：
     func
     Foo::foo_func(11)->: 11
     Bar::operator ()(222)->: 222
    */

    return;
}

int main()
{
    mytest();

    system("pause");
    return 0;
}
```






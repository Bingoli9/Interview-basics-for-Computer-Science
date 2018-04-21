### This指针

每个对象都可是使用一个称为this(一个C++保留字)的指针来访问自己的地址。对象的this指针不是对象本身的一部分，也就是this指针占用的内存大小不会反映在对对象进行的sizeof运算中。相反，this指针作为隐式参数传递给对象的每一个非static成员函数。

对象隐式地使用this指针或者显式地使用this指针来引用它们的数据成员和成员函数。this指针的类型取决于对象的类型以及使用this的成员函数是否被声明为const。例如，在Employee类的非const成员函数中，this指针具有的类型是Employee *const（一个指向非const Employee对象的const指针）。可是在Employee类的const成员函数中，this指针具有的类型为const EMployee * const（指向一个const Employee对象的cost指针）。



this指针可以防止对象的自我赋值。

首先通过一个例子引出自我赋值可能会导致的问题，例子如下：

```c++
class Bitmap {...};
class Widget {
public:
    ...
    Widget& operator=(const Widget& rhs);
    ...
private:
    Bitmap* pb;
};
Widget& Widget::operator=(const Widget& rhs)    //一份不安全的operator=实现版本
{
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
}
```

由于Widget类包含动态分配对象的指针，因而需要自定义拷贝构造函数和赋值符函数。

在上述operator=函数中，如果*this（赋值的目的端）和rhs是同一个对象，将会导致*this对象的pb指针指向一个已被删除的对象。

通过在operator=增加一个证同测试，可以阻止这种错误。代码实现如下：

```c++
Widget& Widget::operator=(const Widget& rhs)    
{
    if(this == &rhs)        //证同测试
        return *this;    
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
}
```


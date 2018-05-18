## *C++中std::tr1::function和bind 组件的使用*

个人的总结：

为什么要使用？

动态装载事件响应函数。

它们可以实现类似函数指针的功能，却比函数指针更加灵活（体现在占位符上面），尤其是在很多成员调用同一个函数（仅仅是参数类型不同）的时候比较方便

这个是函数指针做不到的

要注意的地方：

使用的时候一定要注意指向的是没有this指针的函数（全局函数或静态成员函数），还是有this指针的函数。后面一种必须要用bind()函数。而且要多一个参数。

注意bind的参数顺序： bind（&要调用的函数，&对象， 要调用函数的参数1，要调用函数的参数2...,1(bind函数的参数1),2(bind函数的参数2)...)

占位符号的参数是由 function 调用的时候传入的。 参数可以由function传入，也可由bind实现绑定传入，这两个是可以调整的。

```c++
class Foo
{
public:
void methodA();
void methodInt(int a);
};
class Bar
{
public:
void methodB();
};

boost::function<void()> f1; // 无参数，无返回值

Foo foo;
f1 = boost::bind(&Foo::methodA, &foo);
f1(); // 调用 foo.methodA();
Bar bar;
f1 = boost::bind(&Bar::methodB, &bar);
f1(); // 调用 bar.methodB();

f1 = boost::bind(&Foo::methodInt, &foo, 42);
f1(); // 调用 foo.methodInt(42);

boost::function<void(int)> f2; // int 参数，无返回值
f2 = boost::bind(&Foo::methodInt, &foo, _1);
f2(53); // 调用 foo.methodInt(53);
```

如果没有boost::bind，那么boost::function就什么都不是，而有了bind()，“同一个类的不同对象可以delegate给不同的实现，从而实现不同的行为”（myan语），简直就无敌了。

在C++的TR1中(Technology Report)中包含一个function模板类和bind模板函数，使用它们可以实现类似函数指针的功能，但却却比函数指针更加灵活，特别是函数指向类 的非静态成员函数时。可以参考Scott Meyers. <<Effective C++ (3rd Edition)>>. Item 35.下面具体说明其使用方法。

#### **一、指向全局函数或静态成员函数时**

因为在本质上讲全局函数和静态成员函数没有区 别，使用方法上除了静态成员函数在引用时要在前面加域作用符className::外，没有其它任何区别，事实上全局函数也有可能放入命名空间，或者使用 全局域作用符，例如 nameSpace::function() 或::function，这样不仅本质上相同，形势上也与静态成员函数一致了，所以它们是没有区别的，放到一起讨论。

这种情况比较简单，只需要定义一个类型

```c
#include <iostream>
#include <iomanip>
#include <tr1/memory>
#include <tr1/functional>

typedef std::tr1::function<void (int)> HandlerEvent;

然后再定义一个成员变量

class Sharp{

public:

HandlerEvent handlerEvent;

};

然后在其它函数内就可以通过设置handlerEvent的值来动态装载事件响应函数了，如：

class Rectangle{

private:

std::string name;

Sharp sharp;

public:

void initial(void);

const Sharp getSharp() const;

static void onEvent(int param){ //---------------(1)

std::cout << "invode onEvent method,get parameter: " << param << std::endl;

 }
};

//类的实现方法

void Rectangle::initial(){

sharp.handlerEvent = HandlerEvent(&Rectangle::onEvent); //---------------(2)

std::cout << "invode initial function!" << std::endl;

}

const Sharp Rectangle::getSharp() const{

return sharp;

}

//下面为测试函数:

int main(int argc,char *argv[]){

std::cout <<"hi: " << std::setw(50) << "hello world!" << std::endl;

Rectangle rectangle;

rectangle.initial(); //---------------(3)

rectangle.getSharp().handlerEvent(23); //---------------(4)

}

//输出结果如下：

hi: hello world!

invode initial function!

invode onEvent method,get parameter: 23 //---------------(5)
```

注 意，这里使用了静态成员函数，如果把Rectangle前面的static去掉这段代码不能工作，编译都不能通过，因为静态成员函数与非静态成员函数的参 数表不一样，原型相同的非静态函数比静态成员函数多一个参数，即第一个参数this指针，指向所属的对象，任何非静态成员函数的第一个参数都是this指 针，所以如果把Rectangle前面的static去掉，其函数原型等效于下面的一个全局函数：

*void onEvent(Rectangle\* this, int);*

所 以，这与HandlerEvent所声明的函数类型不匹配，编译将不能通过。而且，既然静态成员函数没有this指针，所以上面(3)处的调用使 sharp对象中的handlerEvent使向了Rectangle的静态方法onEvent(),这样当通过(4)处这样调用时就会自动执行(1)处 的静态函数onEvent()。

#### **二、std::tr1::bind()模板函数的使用**

通过上面的std::tr1::function 可以对静态成员函数进行绑定，但如果要对非静态成员函数的绑定，需用到下机将要介绍的bind()模板函数.

首先说bind的用法，其声明如下所示：

*bind(Function fn, T1 t1, T2 t2, …, TN tN);*

其中fn为将被调用的函数，t1…tN为函数的参数。如果不指明参数，则可以使用占位符表示形参，点位符格式为

std::tr1::placehoders::_1, std::tr1::placehoders::_2, …, std::tr1::placehoders::_N

将上例中Rectangle::onEvent(int param)前的static去掉改为非静态成员函数，则进行动态绑定使得程序正常运行，将Rectangle::initial(void)的定义修改为：

```c++
void Rectangle::initial(){

sharp.handlerEvent = std::tr1::bind(&Rectangle::onEvent,this,std::tr1::placeholders::_1/*因onEvent函数需要一个参数，所以用一占位符*/);

std::cout << "invode initial function!" << std::endl;

}
```

这样，便动态装载函数成功。其它测试数据都不用进行修改。测试结果于上一样。

#### **三、指向虚成员函数的使用**

对 于虚成员函数的情况与上面第2节所说相同，仍然可以实现虑函数的效果。如果定义类Square继承自Rectangle,将 Rectangle::OnEvent重载,定义一个新的Square::OnEvent，Rectangle::initialize中的函数不变，仍 然使用Rectangle::OnEvent进进绑定，则调用成员object.onEvent()时，具体执行Rectangle::OnEvent还 是Square::OnEvent，看object所属对象的静态类型是Rectangle还是Square而定.

*下面为简单示例：*

我们首先修改一个上面Rectangle的initial()方法，改为虚函数。如：

```c
virtual void onEvent(int param){

std::cout << "invode Rectangle's onEvent method,get parameter: " << param << std::endl;

}
然后我们再写一个Square类来继承Rectangle类。并重写onEvent方法。如:

class Square : public Rectangle{

public:

void onEvent(int param){

std::cout << "invode Square's onEvent method,get parameter: " << param << std::endl;

}

};

测试代码：

int main(int argc,char *argv[]){

Rectangle rectangle;

rectangle.initial();

rectangle.getSharp().handlerEvent(23);

Square square;

square.initial();

square.getSharp().handlerEvent(33);

}

运行后的结果如下：

hi: hello world!

invode initial function!

invode Rectangle's onEvent method,get parameter: 23

invode initial function!

invode Square's onEvent method,get parameter: 33

这样我们就可以看到sharp会针对具体对象来调用相应的onEvent()方法。 上面的程序示例读者可自行研习。
```


## C++那些细节--函数指针

# 一.简介

C或者C++中最灵活的东东就是指针了，在操作一个对象，或者数组等等，我们常常用到指针，可以给编程带来很多灵活性。但是，指针不仅仅能指向固定数据类型或是对象，指针还可以指向函数，这就是所谓的函数指针。

有了函数指针，我们可以通过指针调用函数，更重要的是我们可以将函数指针作为参数传递给函数，进而可以进行完成注册，回调等等功能，可以说，有了函数指针，我们的程序可以设计的更加灵活了。

# 二.普通函数指针

## 1.函数指针的定义方式

看一个最简单的例子：

```c
// C++Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;

//定义一个函数指针
void (*pFunc)(int);

//声明并定义一个函数
void PrintInt(int i)
{
	cout<<i<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//将函数赋给函数指针
	//不使用&符号也可以，因为函数名称本来就是函数的首地址，类似数组
	pFunc = &PrintInt;
	
	//通过函数指针来调用函数
	pFunc(1);
	//调用时也可以写的完整规范一些（*pFunc）（1）符合一般指针的标准

	system("pause");
	return 0;
}
```

结果：

1
请按任意键继续. . .

声明函数指针的时候，一般的格式为 返回值 （*函数指针名）（参数1，参数2...）但是这样声明有一个弊端，就是麻烦，每次需要一个函数指针的时候，都需要写这么一大串，很麻烦，所以我们就想到了用typedef这个关键字，定义某一种类型的函数指针，给它一个别名，这样，每次使用这种函数指针的时候就可以像定义一个int型变量那么简单。

比如上面的函数指针，我们就可以这样写：

```c
// C++Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;

//使用typedef定义函数指针,此时，pFunc就不再是函数指针本身的名称，而是这类函数指针的一个别名
typedef void (*pFunc)(int);

//声明并定义一个函数
void PrintInt(int i)
{
	cout<<i<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//定义一个函数指针，并赋予其初始值
	pFunc func = PrintInt;
	
	//通过函数指针来调用函数
	func(1);
	

	system("pause");
	return 0;
}
```

结果：

1
请按任意键继续. . .

这样写之后，我们就定义了一种函数指针的类型，返回值为void，参数为int的函数指针，之后使用pFunc就可以很方便的定义这种类型的函数指针啦！

# 三.成员函数指针

成员函数指针是C++中最麻烦的东东之一，准确的说是非静态成员函数指针。

## 1.静态成员函数指针

静态成员函数指针与普通函数指针一样，我们看一个例子：

```c
// C++Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;

//Base类
class Base
{
public:
	static void Print(int num)
	{
		cout<<num<<endl;
	}
};

//定义一个静态成员函数指针
typedef void (*pFunc)(int);


int _tmain(int argc, _TCHAR* argv[])
{
	//将静态成员函数赋给函数指针
	pFunc func = Base::Print;

	//通过函数指针调用函数
	func(1);

	system("pause");
	return 0;
}
```

结果：

1
请按任意键继续. . .

静态成员函数与普通的函数没有太多区别，虽然他们定义在类中，但是这个成员函数不会因为对象的不同而做出不同的处理，因为它没有this指针，所以我们可以将它看成普通的函数。

## 2.非静态成员函数

但是非静态成员函指针就麻烦得多，原因非静态成员函数有一个隐藏的参数--this指针，这个东东在不同的对象中是不一样的，所以很麻烦。我们定义非静态成员函数指针的时候就需要将对象的类型也写出来。调用的时候，也要根据相应的对象来调用这个函数。看一个例子：

```c
// C++Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;

//Base类
class Base
{
public:
	void Print(int num)
	{
		cout<<num<<endl;
	}
};

//定义一个成员函数指针
typedef void (Base::*pFunc)(int);


int _tmain(int argc, _TCHAR* argv[])
{
	Base base;
	//取成员函数的地址，必须以这种形式，不能以对象的形式获取，而且必须加上&符号
	pFunc func = &Base::Print;
	//调用的时候写法也比较特殊，base.*func表示函数体，是一个整体，需要用（）
	(base.*func)(1);
	
	system("pause");
	return 0;
}
```

结果：

1
请按任意键继续. . .

分析一下成员函数指针的定义和使用，我们这样定义函数指针，（Base：：*pFunc）（int），其实就相当于（*pFunc）（Base*， int），相当于普通的函数指针需要多一个this指针作为参数，而这个this指针在不同的对象中一定是不同的，所以成员函数指针之间是不能互相转化的，只有同类型的对象的函数才能赋给这种对象的函数指针。

在指针赋值的时候，注意一下写法，普通的函数指针在赋值的时候，可以不写&符号，但是成员函数指针赋值的时候比较严格，如果不写的话会报出这样的错误：

error C3867: “Base::Print”: 函数调用缺少参数列表；请使用“&Base::Print”创建指向成员的指针

而且在赋值的时候，不要用对象赋值，要用 类名：：函数名 这种方式赋值，使用 对象名.函数名的时候会报出这样的错误：

 error C2276: “&”: 绑定成员函数表达式上的非法操作

可见，对于成员函数指针的写法还是挺严苛的。

最后再分析一下使用，由于成员函数指针需要一个this指针作为参数，这个参数又不能直接给出，所以我们就只能通过对象来调用函数，在使用函数的时候，由于函数是一个整体，所以需要用（），在括号内部，我们通过*func获得函数，然后前面使用base.就将base作为this指针传递给了函数。

那么，既然这个函数是非静态成员函数，那么这个函数支不支持动态绑定呢？换句话说就是，我们声明的函数指针是基类的函数指针，子类覆写了这个函数，那么，用子类对象调用的时候，是调用基类的函数还是子类的函数呢？我们看一个例子：

```c
// C++Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;

//Base类
class Base
{
public:
	//虚函数
	virtual void Print(int num)
	{
		cout<<"base: "<<num<<endl;
	}
};

class Child : public Base
{
public:
	//覆写基类的Print方法
	void Print(int num) override
	{
		cout<<"child: "<<num<<endl;
	}
};


//定义一个成员函数指针
typedef void (Base::*pFunc)(int);

int _tmain(int argc, _TCHAR* argv[])
{
	Base base;
	Child child;
	//给函数指针赋值的时候，必须是用声明函数指针的类来赋值（此处为Base）
	pFunc func = &(Base::Print);
	//通过base对象调用函数指针
	(base.*func)(1);
	//通过child对象调用函数指针
	(child.*func)(1);
	//查看函数指针的大小
	cout<<"sizeof Member Function: "<<sizeof(func)<<endl;

	system("pause");
	return 0;
}
```

结果：

base: 1
child: 1
sizeof Member Function: 4
请按任意键继续. . .

从上面的结果，我们看出，在最后使用函数指针的时候，这个this指针的对象可以是我们声明函数指针的时候的对象的子类，并且如果我们覆写了基类的函数，是可以调用子类的函数的（注意是覆写基类的virtual函数，如果只是单纯的覆盖是没有多态效果的）。

我们分析一下原因，还是这样看待这个函数指针，把它看成普通函数指针增加了一个类对象的this指针作为参数，这个形参我们可以声明为基类的指针，我们给实参的时候，可以给基类的对象，当然也可以给子类对象，这就跟我们普通函数传递参数的情况一样，然后这个参数传递进去，如果有virtual函数，那么就可以触发多态。但是我们在给函数指针赋值的时候，却只能使用基类的函数，因为我们没有声明子类的函数。

# 五.其他问题

## 函数指针和指针函数

函数指针和指针函数仅仅是名字比较像，写法容易搞混，其他并没有什么联系，二者可以共存。

函数指针我们说过了，就是指向函数的指针，其本质是一个指针。

指针函数，指的是函数的返回值是一个指针，其本质是一个函数。

两者容易搞混的地方就在于写法：

```c
//定义一个函数指针
typedef int (*pFunc)(void);
//定义一个指针函数
int* PointerFunc(void)
{
	int a = 1;
	return &a;
}
```

函数指针*和名字是放在一起的，而指针函数*是和返回值放在一起的。

当然，我们也可以定义一个指针函数的函数指针：

```c
//定义一个指针函数的函数指针
typedef int* (*pFUN)(void);
```


#### 介绍static

static的作用主要有两种:

第一个作用是限定作用域；第二个作用是保持变量内容持久化；

c语言中static的用法：

1、全局静态变量：

　　用法：在全局变量前加上关键字static，全局变量就定义成一个全局静态变量。 static int temp；

　　内存中的位置：静态存储区，在整个程序运行期间一直存在。

　　初始化：未经初始化的全局静态变量会被自动初始化为0（自动对象的值是任意的，除非他被显式初始化）；

　　作用域：全局静态变量在声明他的文件之外是不可见的，准确地说是从定义之处开始，到文件结尾。

2、局部静态变量：

　　在局部变量之前加上关键字static，局部变量就成为一个局部静态变量。

　　内存中的位置：静态存储区

　　初始化：未经初始化的全局静态变量会被自动初始化为0（自动对象的值是任意的，除非他被显式初始化）；

　　作用域：作用域仍为局部作用域，当定义它的函数或者语句块结束的时候，作用域结束。但是当局部静态变量离开作用域后，并没有销毁，而是仍然驻留在内存当中，只不过我们不能再对它进行访问，直到该函数再次被调用，并且值不变；

3、静态函数：

　　在函数返回类型前加关键字static，函数就定义成静态函数。函数的定义和生命在默认情况下都是extern的，但静态函数只是在声明他的文件当中可见，不能被其他文件所用；

c++中static的用法：

　　1、类的静态成员：

```c++
　class A{

　　private:

　　　　static int val;

　　};

int A:: val = 0;

```

　　在实现中必须对他进行初始化，初始化时使用作用域运算符来标明他所属类，其属于该类的所有成员共有，只有一个拷贝；

　　2、类的静态成员函数：

```c++
　class A{

　　private:

　　　　static int func(int x);

　　};

```

　　 实现的时候也不需要static的修饰，因为static是声明性关键字；类的静态函数是该类的范畴内的全局函数，不能访问类的私有成员，只能访问类的静态成员，不需要类的实例即可调用；实际上，他就是增加了类的访问权限的全局函数；

　　int  A::func(int);

　　静态成员函数可以继承和覆盖，但无法是虚函数；

　　3、只在cpp内有效的全局变量：

　　在cpp文件的全局范围内声明：

　　static int val = 0；

　　这个变量的含义是该cpp内有效，但是其他的cpp文件不能访问这个变量；如果有两个cpp文件声明了同名的全局静态变量，那么他们实际上是独立的两个变量；（隐藏）

　　4、只在cpp内有效的全局函数：

　　函数的实现使用static修饰，那么这个函数只可在本cpp内使用，不会同其他cpp中的同名函数引起冲突；

　　warning：不要再头文件中声明static的全局函数，不要在cpp内声明非static的全局函数，如果你要在多个cpp中复用该函数，就把它的声明提到头文件里去，否则cpp内部声明需加上static修饰；

#### C++智能指针具体是怎么管理指针的，怎么防止内存泄漏的。

#### 传递指向指针的引用

`int *&a` ：从右至左理解，a是一个引用，与指向int类型对象的指针绑定。

#### 类

类就是定义了一个新的类型和一个新的作用域。用户代码可以访问类的public成员但是不能访问private成员，private成员只能由基类的成员和友元访问。

#### 指针和引用

指针使用“*” “->”操作符，引用则使用“.”。引用必须初始化，第一次绑定之后不可再修改。指针可以重新赋值

#### 禁止对象建立在栈上

在C++中，为了让某个类只能通过new来创建（即如果直接创建对象，编译器将报错），应该将**析构函数设为私有**。编译器在为类对象分配栈空间时，会先检查类的析构函数的访问性，如果类的析构函数是私有的，则编译器不会在栈空间上为类对象分配内存。 

#### 禁止对象产生在堆上

只有使用 new 运算符，对象才会建立在堆上，因此，只要禁用new运算符就可以

```
class A {
private:
    void* operator new(size_t t){}     // 注意函数的第一个参数和返回值都是固定的
    void operator delete(void* ptr){}  // 重载了new就需要重载delete
};
```

#### 参数传递

如果形参是引用类型，则绑定到对应的实参上，避免了参数拷贝，如果不需要改变实参的值，尽量用常量引用；否则，将实参的值拷贝后赋值给形参，此时对变量的改动不会影响实参初始值。

#### 类的静态成员

可以使用类的对象、引用或者指针来访问静态成员函数；在类外部定义静态成员时不能重复static 关键字；必须在类外部定义和初始化每个静态数据成员

#### final关键字

它的作用是指定类的虚函数不能被该类的继承类重写（override），或者是指定一个类成为一个不能被继承的类（final class）

#### C++单例模式实现

```c++
#ifndef _SINGLETON_H_
#define _SINGLETON_H

#include <iostream>

class Singleton{
	public:
		static Singleton* getInstance();
		
	private:
		Singleton();
		//把复制构造函数和=操作符设为私有，防止被复制
		Singleton(const Singleton&);
		Singleton& operator=(const Singleton&);
		
		static Singleton* instance; 
}; 

#endif

#include "Singleton.h"

Singleton::Singleton()
{
	
}

Singleton::Singleton(const Singleton&){
	
} 

Singleton& Singleton::operator=(const Singleton&) {
	
}

//此处初始化
Singleton* Singleton::instance = new Singleton();
Singleton* Singleton::getInstance(){
	return instance;
}
```

#### map和set底层实现

红黑树

#### 函数调用原理

动态绑定和静态绑定

所谓动态绑定就是一个类的指针或者引用在调用一个虚函数的时候，并不直接指向该函数的地址，而是执行这个类的虚函数表。比如：

```c++
A& a;
a->func();	//假设func()是类A的虚函数
这里的调用关系实质是 A::this->vptr;	//编译阶段就调到这里，
到运行时，就vptr->func(), 这就是所谓的动态绑定
而静态绑定就是
A a;
a.func();//假设func是个虚函数
这里的调用关系就是直接指向func()函数的地址，不通过A::this->vptr,而是直接指向func()的地址
```

#### 同步函数

当一个函数是同步执行时，那么当该函数被调用时不会立即返回，直到该函数所要做的事情全都做完了才返回。

#### 异步函数

如果一个异步函数被调用时，该函数会立即返回，尽管该函数规定的操作任务还没有完成。

#### core dump

产生的原因：内存访问越界、非法指针、堆栈溢出。调试：gdb exec_file core_file , 然后 bt 

#### 虚继承

虚基类是用关键字virtual声明继承的父类，虚继承的特点是，在多重继承下保证基类在子类中拥有唯一的实例。在任何派生类中的virtual基类总用同一个（共享）对象来表示，即便该基类在多条链路上被一个子类继承，但是该子类中只包含一个该虚基类的备份，虚基类主要用来解决继承中的二义性问题。

```c++
class CBase { }；
class CDerive1：virtual public CBase{ }；
class CDerive2：virtual public CBase{ }；
class CDerive12：public CDerive1，CDerive2{ }；
则在类 CDerive12 的对象中，仅有类 CBase 的一个对象数据
```

#### new 和 malloc 的区别？

- new是运算符，malloc()是一个库函数；
- new会调用构造函数，malloc不会；
- new返回指定类型指针，malloc返回`void*`指针；
- new会自动计算需分配的空间，malloc不行；
- new可以被重载，malloc不能。

#### vector、map/multimap、unordered_map/unordered_multimap的底层数据结构，以及几种map容器如何选择？

vector基于数组，multiset, map, multimap基于红黑树，unordered_map/unordered_multimap基于哈希表。

- map/unordered_map 不允许重复元素
- multimap/unordered_multimap允许重复元素
- map/multimap底层基于红黑树，元素自动有序，且插入、删除效率高
- unordered_map/unordered_multimap底层基于哈希表，故元素无序，查找效率高。

#### 栈溢出的原因及解决办法

栈的大小一般默认为1M左右，导致栈溢出的常见原因有两个：

- 函数调用层次过深，每调用一次就压一次栈。
- 局部变量占用空间太大。

解决方法：使用堆，动态申请内存、static修饰

#### core产生的原因，如何调试定位问题？

原因大致有：

- 内存访问越界
- 非法指针
- 堆栈溢出

#### 说几个C++11的新特性。

- auto类型推导
- 范围for循环
- lambda函数
- override 和 final 关键字
- 空指针常量nullptr
- 线程支持、智能指针等

#### static_cast 和 dynamic_cast 的区别

这两个都是C++中的RTTI的两个操作符，它们之间的主要区别是：

- cast发生的时间不同，一个是static编译时，一个是runtime运行时；
- static_cast是相当于C的强制类型转换，用起来可能有一点危险，不提供运行时的检查来确保转换的安全性。
- dynamic_cast用于转换指针和和引用，不能用来转换对象 —— 主要用于类层次间的上行转换和下行转换，还可以用于类之间的交叉转换。在类层次间进行上行转换时，dynamic_cast和static_cast的效果是一样的；在进行下行转换时，dynamic_cast具有类型检查的功能，比static_cast更安全。在多态类型之间的转换主要使用dynamic_cast，因为类型提供了运行时信息。


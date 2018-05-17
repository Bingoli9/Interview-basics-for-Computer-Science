## 嵌套类  Nested类

```
/*
嵌套类

nested class 嵌套类的引入是为了更好的命名空间使用。
嵌套类是名字在其外围类的作用域中可见，但在其他类作用域或定义外围类的作用域中不可见。
嵌套类的名字将不会与另一作用域中声明的名字冲突。

但嵌套类是独立的类，基本上与他们的外围类不相关，因此外围类和嵌套类的“对象”是互相独立的。
嵌套类型的对象不具备外围类所定义的成员，同样，外围类的成员也不具备嵌套类所定义的成员。

区别：类声明、定义 与 类对象访问成员的区别。

本例题来源于： Morgan Stanley 实习生招聘 Online Test （C++）
*/

#include <iostream>
using namespace std;

class Outer
{
public:
	static int m_Out;
	void outDisplay();

	class Inner
	{
	public:
		static int m_In;
		void inDisplay();
	};

};

int Outer::m_Out=10;
int Outer::Inner::m_In=25;
void Outer::outDisplay()
{
	std::cout<<m_Out<<std::endl; //
//	std::cout<<m_In<<std::endl;  // error, m_In is invisible
	std::cout<<Inner::m_In<<std::endl;  //
}

void Outer::Inner::inDisplay()
{
	std::cout<<m_Out<<std::endl; // m_Out在内部类中查找不到，去外部类作用域中查找
	std::cout<<m_In<<std::endl;  // 
}

int  main()
{
	Outer objOut;
	Outer::Inner objIn;

	objIn.inDisplay();
	//objIn.m_Out; //error, access is forbidden 
	//objIn.Outer::m_Out; //error, access is forbidden 
	
	objOut.m_Out;
	objOut.outDisplay();

	//objOut.m_In; // error,cannot pass compiling
	//objOut.Inner::m_In; //error, access is forbidden ，cannot pass compiling
     return 0;
}

```


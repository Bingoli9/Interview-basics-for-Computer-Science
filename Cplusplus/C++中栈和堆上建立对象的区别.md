# [C++中栈和堆上建立对象的区别](http://www.cnblogs.com/xiaoxiaoqiang001/p/5557704.html)

在C++中类的对象建立分为两种，一种是静态建立，如A a；另一种是动态建立，如A* p=new A()，A*p=(A*)malloc()；静态建立一个类对象，是由编译器为对象在栈空间中分配内存，通过直接移动栈顶指针挪出适当的空间，然后在这片内存空间上调用构造函数形成一个栈对象。动态建立类对象，是使用new运算符将对象建立在堆空间中，在栈中只保留了指向该对象的指针。栈是由编译器自动分配释放 ，存放函数的参数值，局部变量的值，对象的引用地址等。其操作方式类似于数据结构中的栈，通常都是被调用时处于存储空间中，调用完毕立即释放。堆中通常保存程序运行时动态创建的对象，C++堆中存放的对象需要由程序员分配释放，它存在程序运行的整个生命期，直到程序结束由OS释放。而在java中通常类的对象都分配在堆中，对象的回收由虚拟机的GC垃圾回收机制决定。

## placement new

new: 分配内存空间并构造对象，返回对应的指针  
delete： 释放内存空间并析构对象  
operator new：重载，但是不能在全局对原型为void operator new(size_t size)这个原型进行重载，一般只能在类中进行重载。  
如果类中没有重载operator new,那么调用的就是全局 ::operator new来完成堆分配。    
operator new[], operator delete, operator delete[]

place new: operator new一个重载版本。目的是在已经分配的内存中创建一个对象。 placement new可以在一个预先准备好了的内存缓冲区中进行，  
不需要查找内存，内存分配时间是常数，而且不会出现在程序运行中途出现内存不足的异常。   MyClass* pClass = new(buf) MyClass;  

   
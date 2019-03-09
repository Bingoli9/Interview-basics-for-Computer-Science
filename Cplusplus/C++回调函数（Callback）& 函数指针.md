## 浅谈C/C++回调函数（Callback）& 函数指针

**摘要**：回调函数就是一个通过函数指针调用的函数。如果你把函数的指针（地址）作为参数传递给另一个函数，当这个指针被用来调用其所指向的函数时，我们就说这是回调函数。回调函数不是由该函数的实现方直接调用，而是在特定的事件或条件发生时由另外的一方调用的，用于对该事件或条件进行响应。

```c++
#include <stdio.h>
//回调函数
int ADD(int (*callback)(int,int), int a, int b){
	return (*callback)(a,b);//此处回调add函数...
}
//普通函数
int add(int a, int b){
	return a + b;
}

int main(void){
	printf("%d\n",add(1,2));
	printf("%d\n",ADD(add,1,2));
	return 0;
}
```

从上面的定义及其实现可以看出，回调函数必须有函数指针的存在，而这里函数指针一般可以先typedef一下，然后再使用，

一般格式： 返回值 (*指针名) (参数列表)

```c++
#include <stdio.h>

//返回值(*指针名)(参数列表)
typedef int (*callback)(int,int);
//回调函数
int ADD(callback p, int a, int b){
	return (*p)(a,b);//此处回调add函数...
}
//普通函数
int add(int a, int b){
	return a + b;
}

int main(void){
	printf("%d\n",add(1,2));
	printf("%d\n",ADD(add,1,2));
	return 0;
}
```

可是，根据上面的例子，回调函数搞得这么麻烦，貌似并没有什么大作用.....纠结！

别纠结，来看一下库函数中的sort排序是怎么弄的。algorithm它提供了某些排序算法的实现（如冒泡排序、快速排序、shell排序、shake排序等等），为了能让库更加通用，不想在函数中嵌入排序逻辑，而让使用者来实现相应的逻辑；或者，能让库可用于多种数据类型（int、float、string），此时，该怎么办呢？可以使用函数指针，并进行回调，如下：

```c++
#include <stdio.h>
#include <algorithm>

bool cmp(int a, int b){
	return a > b;
}
int main(void){
	int a[8] = {5,43,1,7,8,13,0,74};
	std::sort(a,a+10,cmp);//callback
	return 0;
}

```

这里只是提及了一下库函数中的排序问题，如果想了解更多，可以去看一下《[泛型编程与C++标准模板库 : 浅谈sort()排序函数](http://blog.csdn.net/qingdujun/article/details/38342951)》这篇文章。

## c++11 std_function 用法

c++中可调用实体为

- 函数
- 函数指针
- 函数引用

c++11 新增对象std::function对象，std::function对象是对c++中现有的可调用实体的一种类型安全的包裹。

举例

```c++
#include < functional>  

std::function< size_t (const char*) > print_func;  

/// normal function -> std::function object  
size_t CPrint(const char*) { ... }  
print_func = CPrint;  
print_func("hello world"):  

/// functor -> std::function object  
class CxxPrint  
{  
public:  
    size_t operator()(const char*) { ... }  
};  
CxxPrint p;  
print_func = p;  
print_func("hello world");    
```



#### 对于std::function< size_t (const char*) > func的解释

- size_t是返回值
- const char*是参数类型

### 使用std::function作为函数入参

1. #### 基于传值的方式传递参数

   参看下面一段代码，实现了一个注册回调函数的机制，

   ```false
   #include <fonctional>
   void registerCallBack(std::function<void()>);
   ```

   入参std::function<void()>是一个模板类对象，它可以用一个函数签名为void()的可调用对象来进行初始化；上述实现里面是一个传值调用。我们来看一下它的调用过程，

   ```false
   // 方法（A）
   registerCallBack([=]{
       ....  // 回调函数的实现部分
   })
   ```

   这里使用了lambda表达式作为函数的入参，正如前面所说的lambda表达式会生成一个匿名的闭包（closure），基于这个闭包构造了一个std::function<void()>的对象，然后通过传值调用的方式把这个对象传递registerCallBack函数中使用。

2. #### 基于引用的方式传递参数

   当然我们还可以如下实现这个注册函数，入参通过const引用的方式传递，这里的引用必须是const的，这是因为调用registerCallBack函数的地方生成了一个临时的std::function()对象，是一个右值，否则编译会报错。

   ```
   //方法(B)
   void registerCallBack(std::function<void()> const&)

   ```

   这两者的区别就在于，在registerCallBack函数内部怎么使用这个入参，如果只是简单的调用一下std::func()类，那么两种都没有问题，可能使用引用的效率更高；如果register函数内部需要保存这个std::func()，并用于以后使用，那么方法A直接保存没有问题，方法B就必须做一次拷贝，否则方法B中，当临时的对象销毁时，有可能出现引用悬空的问题。
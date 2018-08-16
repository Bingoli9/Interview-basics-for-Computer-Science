## C++11 auto

auto可以在声明变量的时候根据变量初始值的类型自动为此变量选择匹配的类型，类似的关键字还有decltype。举个例子：

```
int a = 10;
auto au_a = a;//自动类型推断，au_a为int类型
cout << typeid(au_a).name() << endl;
```

typeid运算符可以输出变量的类型。程序的运行结果输出了 int

## auto的用法

上面举的这个例子很简单，在真正编程的时候也不建议这样来使用auto，直接写出变量的类型更加清晰易懂。下面列举auto关键字的正确用法。

### 用于代替冗长复杂、变量使用范围专一的变量声明。

```c++
#include<string>
#include<vector>
int main()
{
    std::vector<std::string> vs;
    for (auto i = vs.begin(); i != vs.end(); i++)
    {
        //..
    }
}
```

### 在定义模板函数时，用于声明依赖模板参数的变量类型。

```
emplate <typename _Tx,typename _Ty>
void Multiply(_Tx x, _Ty y)
{
    auto v = x*y;
    std::cout << v;
}
```

若不使用auto变量来声明v，那这个函数就难定义啦，不到编译的时候，谁知道x*y的真正类型是什么呢？

### 注意事项

- auto 变量必须在定义时初始化，这类似于const关键字。
- 定义在一个auto序列的变量必须始终推导成同一类型。例如：


- ```
  auto a4 = 10, a5 = 20, a6 = 30;//正确
  auto b4 = 10, b5 = 20.0, b6 = 'a';//错误,没有推导为同一类型
  ```

  使用auto关键字做类型自动推导时，依次施加一下规则：

- 如果初始化表达式是引用，则去除引用语义。

  ```
  int a = 10;
  int &b = a;

  auto c = b;//c的类型为int而非int&（去除引用）
  auto &d = b;//此时c的类型才为int&

  c = 100;//a =10;
  d = 100;//a =100;
  ```

- 如果初始化表达式为const或volatile（或者两者兼有），则除去const/volatile语义。

  ```
  const int a1 = 10;
  auto  b1= a1; //b1的类型为int而非const int（去除const）
  const auto c1 = a1;//此时c1的类型为const int
  b1 = 100;//合法
  c1 = 100;//非法
  ```

- 如果auto关键字带上&号，则不去除const语意。

  ```
  const int a2 = 10;
  auto &b2 = a2;//因为auto带上&，故不去除const，b2类型为const int
  b2 = 10; //非法
  ```

  这是因为如何去掉了const，则b2为a2的非const引用，通过b2可以改变a2的值，则显然是不合理的。

- 初始化表达式为数组时，auto关键字推导类型为指针。

  ```
  int a3[3] = { 1, 2, 3 };
  auto b3 = a3;
  cout << typeid(b3).name() << endl;
  ```

  程序将输出

  > int *

- 若表达式为数组且auto带上&，则推导类型为数组类型。

  ```
  int a7[3] = { 1, 2, 3 };
  auto & b7 = a7;
  cout << typeid(b7).name() << endl;
  ```

  程序输出

  > int [3]

- 函数或者模板参数不能被声明为auto

  ```
  void func(auto a)  //错误
  {
  //... 
  }
  ```

- 时刻要注意auto并不是一个真正的类型。
  auto仅仅是一个占位符，它并不是一个真正的类型，不能使用一些以类型为操作数的操作符，如sizeof或者typeid。

  ```
  cout << sizeof(auto) << endl;//错误
  cout << typeid(auto).name() << endl;//错误
  ```
## lambda

#### definition

```C++
[capture list] (params list) mutable exception-> return type {
    function body.
}
```

- capture list: extern variables list captured
- params list: 
- mutable: indicates whether extern variables is mutable or not
- exception
- return type
- function body

**some format to define lambda**

| 序号 | 格式                                                        |
| ---- | ----------------------------------------------------------- |
| 1    | [capture list] (params list) -> return type {function body} |
| 2    | [capture list] (params list) {function body}                |
| 3    | [capture list] {function body}                              |

- Format 1 declares const-type expressions that cannot modify values in the capture list
- Format 2 omits the return value type, but the compiler can infer the return type of a lambda expression from the following rules: (1): if a return statement exists in function body, the return type of the lambda expression is determined by the return type of the return statement; （2）if there is no return statement in function body, the return value is of type void.
- Format 3 omits the parameter list, similar to the no-parameter function in normal funcitons. 

**Example**

```C++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(int a, int b)
{
    return  a < b;
}

int main()
{
    vector<int> myvec{ 3, 2, 5, 7, 3, 2 };
    vector<int> lbvec(myvec);

    sort(myvec.begin(), myvec.end(), cmp); // 旧式做法
    cout << "predicate function:" << endl;
    for (int it : myvec)
        cout << it << ' ';
    cout << endl;

    sort(lbvec.begin(), lbvec.end(), [](int a, int b) -> bool { return a < b; });   // Lambda表达式
    cout << "lambda expression:" << endl;
    for (int it : lbvec)
        cout << it << ' ';
}
```

### capture external variables

```C++
#include <iostream>
using namespace std;

int main()
{
    int a = 123;
    auto f = [a] { cout << a << endl; }; 
    f(); // 输出：123

    //或通过“函数体”后面的‘()’传入参数
    auto x = [](int a){cout << a << endl;}(123); 
}
```

- capture value

  ```C++
  int main()
  {
      int a = 123;
      auto f = [a] { cout << a << endl; }; 
      a = 321;
      f(); // 输出：123
  }
  ```

- capture reference

  ```C++
  int main()
  {
      int a = 123;
      auto f = [&a] { cout << a << endl; }; 
      a = 321;
      f(); // 输出：321
  }
  ```

- implicity capture

  Compiler can infer extern variables from function body. This kind of capture method is called implicity capture. 

  Implicity capture comes in two forms, [=] and [&]. [=] means external vatiables are captured by value, and [&] means external variables are captured by reference.

  ```C++
  int main()
  {
      int a = 123;
      auto f = [&] { cout << a << endl; };    // 引用捕获
      a = 321;
      f(); // 输出：321
  }
  ```

- mixed mode capture

| []          | 不捕获任何外部变量                                           |
| ----------- | ------------------------------------------------------------ |
| [变量名, …] | 默认以值得形式捕获指定的多个外部变量（用逗号分隔），如果引用捕获，需要显示声明（使用&说明符） |
| [this]      | 以值的形式捕获this指针                                       |
| [=]         | 以值的形式捕获所有外部变量                                   |
| [&]         | 以引用形式捕获所有外部变量                                   |
| [=, &x]     | 变量x以引用形式捕获，其余变量以传值形式捕获                  |
| [&, x]      | 变量x以值的形式捕获，其余变量以引用形式捕获                  |

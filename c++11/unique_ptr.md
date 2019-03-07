## C++ 11 创建和使用 unique_ptr

unique_ptr不共享它的指针。它无法复制到其他unique_ptr，无法通过值传递到函数，页无法用于需要副本的任何标准模板库算法。只能移动unique_ptr。即，内存资源所有权将转移到另一**unique_ptr**，并且原始 **unique_ptr** 不再拥有此资源。

#### **1、如何创建unique_ptr**

unique_ptr不像shared_ptr一样拥有标准库函数make_shared来创建一个shared_ptr实例。要想创建一个unique_ptr，我们需要将一个new 操作符返回的指针传递给unique_ptr的构造函数。

示例：

```c++
int main()
{
    // 创建一个unique_ptr实例
    unique_ptr<int> pInt(new int(5));
    cout << *pInt;
}
```

#### **2、无法进行复制构造和赋值操作**

unique_ptr没有copy构造函数，不支持普通的拷贝和赋值操作。

```c++
int main() 
{
    // 创建一个unique_ptr实例
    unique_ptr<int> pInt(new int(5));
    unique_ptr<int> pInt2(pInt);    // 报错
    unique_ptr<int> pInt3 = pInt;   // 报错
}
```

#### **3、可以进行移动构造和移动赋值操作**

unique_ptr虽然没有支持普通的拷贝和赋值操作，但却提供了一种移动机制来将指针的所有权从一个unique_ptr转移给另一个unique_ptr。如果需要转移所有权，可以使用std::move()函数。

```c++
int main() 
{
    unique_ptr<int> pInt(new int(5));
    unique_ptr<int> pInt2 = std::move(pInt);    // 转移所有权
    //cout << *pInt << endl; // 出错，pInt为空
    cout << *pInt2 << endl;
    unique_ptr<int> pInt3(std::move(pInt2));
}
```

#### **4、可以返回unique_ptr**

unique_ptr不支持拷贝操作，但却有一个例外：可以从函数中返回一个unique_ptr。

```c++
unique_ptr<int> clone(int p)
{
    unique_ptr<int> pInt(new int(p));
    return pInt;    // 返回unique_ptr
}

int main() {
    int p = 5;
    unique_ptr<int> ret = clone(p);
    cout << *ret << endl;
}
```

## unique_ptr使用场景

#### **1、为动态申请的资源提供异常安全保证**

```c++
void Func()
{
    int *p = new int(5);

    // ...（可能会抛出异常）

    delete p;
}
```

这是我们传统的写法：当我们动态申请内存后，有可能我们接下来的代码由于抛出异常或者提前退出（if语句）而没有执行delete操作。

解决的方法是使用unique_ptr来管理动态内存，只要unique_ptr指针创建成功，其析构函数都会被调用。确保动态资源被释放。

```c++
void Func()
{
    unique_ptr<int> p(new int(5));

    // ...（可能会抛出异常）
}
```

#### **2、返回函数内动态申请资源的所有权**

```
unique_ptr<int> Func(int p)
{
    unique_ptr<int> pInt(new int(p));
    return pInt;    // 返回unique_ptr
}

int main() {
    int p = 5;
    unique_ptr<int> ret = Func(p);
    cout << *ret << endl;
    // 函数结束后，自动释放资源
}
```

#### **3、在容器中保存指针**

```c++
int main() 
{
    vector<unique_ptr<int>> vec;
    unique_ptr<int> p(new int(5));
    vec.push_back(std::move(p));    // 使用移动语义
}
```

#### 4、管理动态数组

标准库提供了一个可以管理动态数组的unique_ptr版本。

```c++
int main() 
{
    unique_ptr<int[]> p(new int[5] {1, 2, 3, 4, 5});
    p[0] = 0;   // 重载了operator[]
}
```


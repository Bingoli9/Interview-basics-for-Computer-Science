## nullptr

Why not use **NULL**?

Using example to expose the **NULL** 's  problem.

```C++
//示例代码1.0 http://www.cnblogs.com/feng-sc/p/5710724.html
class Test
{
public:
    void TestWork(int index)
    {
        std::cout << "TestWork 1" << std::endl;
    }
    void TestWork(int * index)
    {
        std::cout << "TestWork 2" << std::endl;
    }
};

int main()
{
    Test test;
    test.TestWork(NULL);
    test.TestWork(nullptr);
}
```

```C++
result:
TestWork 1
TestWork 2
```


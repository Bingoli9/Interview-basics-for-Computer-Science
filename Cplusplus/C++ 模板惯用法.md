## C++ 模板惯用法

- 堆栈上分配
- 编译优化开关
- 推导数组元素个数
- 推导常数
- 隐式转换的显式函数implicit_cast
- 推导callable可调用物
- 用成员模板实现继承隐喻
- 假设模板基类中的成员
- CRTP循环模板牧师
- 结合使用函数模板和类模板
- 特化的基本目的
- 解决实例化代码膨胀
- traits特征和policy策略

#### 堆栈分配

on-stack allocation 的 std 案例：tr1::array 模板

使用模板方法的不足之处是使用编译时确定的 buffer size，为了能在运行时动态调整 stack 内存分配数量，可借助 VC CRT 的 _alloca, _malloca 函数

示例：一个 printf 式的生成 std::string 的函数

```C++
template <size_t BufSize, class CharT>  
inline  
std::basic_string<CharT> make_string(const CharT* format, ...)  
{  
    CharT buf[BufSize];  
    va_list args;  
  
    va_start(args, format);  
    // vsprintf 是函数模板, 其针对 char 特化调用 vsprintf_s, 针对 wchar_t 特化调用 vswprintf_s  
    vsprintf(buf, BufSize, format, args);  
    va_end(args);  
  
    // 注意: 返回时构造可让 VC 编译优化为只有一次 string ctor 调用, 没有额外 copy  
    return std::basic_string<CharT>(buf);  
}  
```

#### 编译优化开关

bool 模板参数， 或整数模板参数 + 阈值， 避免重复代码时借助编译优化

```C++
template <bool UseMask>  
void blit(int* dst, const int* src, int mask, size_t size)  
{  
    for (size_t i = 0; i < size; i++, dst++, src++) {  
        if (!UseMask || *src != mask)  
            *dst = *src;  
    }  
}  
```

#### 推导数组元素个数

可由参数推导求出数组的元素个数，要求必须是数组名，而非指向数组的指针或new[]数组

```C++
// 以 C++ 方式编译时, _countof 的定义如下  
template <typename _CountofType, size_t _SizeOfArray>  
char (*__countof_helper(UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];  
#define _countof(_Array) (sizeof(*__countof_helper(_Array)) + 0)  
```

```C++
template <size_t size>  
errno_t strcpy_s(char (&strDestination)[size], const char *strSource);  
```

#### 推导常数

```C++
#define _MASK_VAL(x)    (1 << x)  
// 用于代替上面的宏  
// 实例化超出 [0:31] 范围的 Mask 时, 产生编译警告 warning C4293  
template <unsigned int N>  
struct Mask {  
    enum { Value = (1 << N) };  
};  
```

#### 隐式转换的显式函数 implicit_cast

1. 因为是 return u，而不是 return (T) u，所以是隐式转换
2. 可推导的参数放到 template 参数列表的最后
3. 效率：有两次拷贝（参数、返回值），但通常编译优化可将其减小到一次拷贝

```C++
template <class T, class U> T implicit_cast(U u) { return u; }  
  
void func(int i)  
{  
    implicit_cast<double>(i);       // T 显式指定为 double, U 由参数推导得出 int  
    implicit_cast<char, double>(i); // i 先转换为 double, 再隐式转换为 char  
    implicit_cast<char*>(i);        // 错误: int 不能隐式转换为 char*  
}  
```

#### 推导callable可调用物


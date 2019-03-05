## C++17 new feature

#### 非类型模板参数auto

There are two types of template parameters. One is type template parameter, which is the one we use most often:

```C++
template <typename T, typename U>
auto add(T t, U u) {
    return t+u;
}
```

There are two types of template parameters. One is the type template parameter and the one we use most often: T and U are both type template parameters.The other is a non-typed template parameter that allows different literals to be used as template parameters:

```C++

template <typename T, int BufSize>
class buffer_t {
public:
    T& alloc();
    void free(T& item);
private:
    T data[BufSize];
}
 
buffer_t<int, 100> buf; // 100 作为模板参数！
```

Unfortunately, we have to specify the specific types of non-typed template parameters when writing templates. C++17 breaks this limitation and allows us to use the **auto** keyword in non-typed template parameters, thus allowing the compiler to derive specific types:

```C++
template <auto value> void foo() {
    return;
}
 
foo<10>();  // value 被推导为 int 类型

```

#### std::variant\<\>

**std::variant** can store multi-type variables.

```C++
#include <variant>
template <size_t n, typename... Args>
std::variant<Args...> _tuple_index(size_t i, const std::tuple<Args...>& tpl) {
    if (i == n)
        return std::get<n>(tpl);
    else if (n == sizeof...(Args) - 1)
        throw std::out_of_range("越界.");
    else
        return _tuple_index<(n < sizeof...(Args)-1 ? n+1 : 0)>(i, tpl);
}
template <typename... Args>
std::variant<Args...> tuple_index(size_t i, const std::tuple<Args...>& tpl) {
    return _tuple_index<0>(i, tpl);
}

```

 #### Structured bindings

Offering multiple return functionality

```C++
std::tuple<int,double,std::string> f() {
    return std::make_tuple(1,2.3,"456");
}
auto [x,y,z] = f(); // x,y,z 分别被推导为int,double,std::string

```


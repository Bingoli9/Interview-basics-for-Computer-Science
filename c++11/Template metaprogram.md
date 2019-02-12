### Template metaprogram

### meta-template basic conception

A template meta-program consists of metadata and meta-function

Metadata is data that a meta-program can manipulate, that is, a C++ compiler can manipulate at compile time. Metadata is not a run-time variable; it can only be a compile-time constant and cannot be modified. Common metadata types include enum enumerated constans, static constants, basic types, and custom types.

Metafunction is used in template metaprogram to manipulate and process metadata. It can be "called" at compile time, because its function and form is similar to the function at run time. It is called metafunction, and it is the most important component in metaprogram. A metafunction is actually a class, template class, or template class, or template funciton in C++, usually in the following form:

```C++
template<int N, int M>
struct meta_func{
	static const int value = N+M;
}
```

meta_func is executed in compile time, and there's no calculation in execute time.

### type_traits

type_traits is a template metamodel library provided by C++11. Type_traits can be used to calculate, qury, judge, transform and select at compile time., providing some common metafuns needed by template metaprogram. 

Tem simplies type_traits is the **integral_constant** meta-function that defines compile-time.

```C++
template< class T, T v>
struct integral_constant;
```

With this simple traits, it's easy to define compile-time constants, such as an int with a value of 1.

```C++
Using one_type = STD ::integral_constant<int, 1>;
```

or

```C++
template<class T>
struct one_type : std::integral_constant<int, 1>{};
```

To get the constant value by using the following code:

```C++
one_type::value
```

some example:

```C++
#include <iostream>
#include <type_traits>

int main() {
  std::cout << "int: " << std::is_const<int>::value << std::endl;
  std::cout << "const int: " << std::is_const<const int>::value << std::endl;

  //判断类型是否相同
  std::cout<< std::is_same<int, int>::value<<"\n";// true
  std::cout<< std::is_same<int, unsignedint>::value<<"\n";// false

  //添加、移除const
  cout << std::is_same<const int, add_const<int>::type>::value << endl;
  cout << std::is_same<int, remove_const<const int>::type>::value << endl;

  //添加引用
  cout << std::is_same<int&, add_lvalue_reference<int>::type>::value << endl;
  cout << std::is_same<int&&, add_rvalue_reference<int>::type>::value << endl;

  //取公共类型
  typedef std::common_type<unsigned char, short, int>::type NumericType;
  cout << std::is_same<int, NumericType>::value << endl;

  return 0;
}
```

### std::decay

**std::decay** is used to remove the reference aand CV qualification, and can simplify our programming.  In addition to the generic useage in base type, **decay** can be used with arrays and functions.

```C++
typedef std::decay<int>::type A;           // int
typedef std::decay<int&>::type B;          // int
typedef std::decay<int&&>::type C;         // int
typedef std::decay<constint&>::type D;    // int
typedef std::decay<int[2]>::type E;        // int*
typedef std::decay<int(int)>::type F;      // int(*)(int)
```

### template meta-program application

#### function_traits 

function_traits is used to get the functional sematics of callable object properities such as function type, return type, function pointer type, and parameter type. 

```C++
template<typename T>
struct function_traits;

//普通函数
template<typename Ret, typename... Args>
struct function_traits<Ret(Args...)>
{
public:
    enum { arity = sizeof...(Args) };
    typedef Ret function_type(Args...);
    typedef Ret return_type;
    using stl_function_type = std::function<function_type>;
    typedef Ret(*pointer)(Args...);

    template<size_t I>
    struct args
    {
        static_assert(I < arity, "index is out of range, index must less than sizeof Args");
        using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
    };
};

//函数指针
template<typename Ret, typename... Args>
struct function_traits<Ret(*)(Args...)> : function_traits<Ret(Args...)>{};

//std::function
template <typename Ret, typename... Args>
struct function_traits<std::function<Ret(Args...)>> : function_traits<Ret(Args...)>{};

//member function
#define FUNCTION_TRAITS(...) \
    template <typename ReturnType, typename ClassType, typename... Args>\
    struct function_traits<ReturnType(ClassType::*)(Args...) __VA_ARGS__> : function_traits<ReturnType(Args...)>{}; \

FUNCTION_TRAITS()
FUNCTION_TRAITS(const)
FUNCTION_TRAITS(volatile)
FUNCTION_TRAITS(const volatile)

//函数对象
template<typename Callable>
struct function_traits : function_traits<decltype(&Callable::operator())>{};
```


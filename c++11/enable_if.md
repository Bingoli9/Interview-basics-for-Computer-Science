## enable_if

Enable type if the condition is met.

The type T is enabled as member type enable_if::type if Cond is true. Otherwise, enable_if::type is not defined.

#### In order to better understand the implementation way of **std::enable_if<>**, we need to understand **SFINAE**.

**SFINAE**: Substitution Failure Is Not An Error

**SFINAE** prunes functions that do not yield valid template instantiations from a set of overload functions.

**SFINAE** is apply widely in std::enable_if. In the process of template argument deduction, a C++ compiler attempts to instantiate signatures of a number of candidate overloaded functions to make sure that exactly one overloaded function is available as a perfect match for a given function call.

If an invalid argument or  return type is formed during the instantiation of a function template, the instantiations is removed from the overload resolution set instead of causing a compliation error.

As long as there is one and only one function to which the call can be dispathced, the compiler issues no errors.

The implementation mechanism of **std::enable_if\<\>** is shown as following code:

```C++
template<bool Cond, typename T = void> struct enable_if {}
template<typename T> struct enable_if<true, T> {typedef T type;}
```

Example:

```C++
// enable_if example: two ways of using enable_if
#include <iostream>
#include <type_traits>

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename std::enable_if<std::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
template < class T,
           class = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even (T i) {return !bool(i%2);}

int main() {

  short int i = 1;    // code does not compile if type of i is not integral

  std::cout << std::boolalpha;
  std::cout << "i is odd: " << is_odd(i) << std::endl;
  std::cout << "i is even: " << is_even(i) << std::endl;

  return 0;
}
```


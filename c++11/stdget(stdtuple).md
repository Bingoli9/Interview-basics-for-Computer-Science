## std::get(std::tuple)

```C++
std::get<I>(_tuple)
```

Extract the Ith element from the tuple. I must be an integer value in [0, sizeof...(Types)]

#### Parameters

t tuple whose contents to extract

#### return value

A reference to selected element of t

```C++
#include <iostream>
#include <string>
#include <tuple>
 
int main()
{
    auto t = std::make_tuple(1, "Foo", 3.14);
    // index-based access
    std::cout << "(" << std::get<0>(t) << ", " << std::get<1>(t)
              << ", " << std::get<2>(t) << ")\n";
    // type-based access
    std::cout << "(" << std::get<int>(t) << ", " << std::get<const char*>(t)
              << ", " << std::get<double>(t) << ")\n";
    // Note: std::tie and structured binding may also be used to decompose a tuple
}
```

Output:

```
(1, Foo, 3.14)
(1, Foo, 3.14)
```

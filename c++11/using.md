## using

#### define alias

```C++
template<class T>
using Tlist = std::list<T>
```

```C++
//typedef void (*df)()
using df = void(*)()
```

#### use extern struct

```C++
using A::A;
```

#### use extern type

```C++
using typename A;
```

#### overload parents' function

using definition introduces base class member in derived class.

```C++

class Base {
public:
std::size_t size() const { return n; }
protected:
std::size_t n;
};

class Derived : private Base {
public:
using Base::size;
protected:
using Base::n;
// ...
};

```

Consider the following situation:

As we all known,  if derived class has function which name is the same as base class, then we should consider its rule:

- If derived member function has the same name as base class, but the argument is different, then, wether has "virtual" key word, base class's function will be hidden.
- If derived member function has the same name as base class as well as the same argument, but base class function does not have "virtual" key word, then base class's function will be hidden.

Using key word "using", we can explicit expose base class's specific function.

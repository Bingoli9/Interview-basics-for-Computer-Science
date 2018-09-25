### new(p) T1(value)

place new，在指针p所指向的内存空间创建一个类型为T1的对象。可以简单的理解为C中的realloc，在已有空间的基础上，重新分配一个空间，可以不破坏原来的数据，也可以用新的数据覆盖。

### 模板函数参数推导

```c++
`template``<``class` `T> ``void` `foo(T v1){};``  ``foo<``double``>(3);`
```

但是，调用模板函数时，如果不显式指明模板参数，而是根据函数的调用实参去推断模板实参，这就是模板参数推导。例如上例可进一步考虑情形：

```c++
`  ``foo(3.14);`
```

编译器会推导出这种函数调用的模板实参为T->double。

### typename与class的区别

```c++
//这里class和typename是相同的
template <class T>
template <typename T>
```

```c++
//在这里，typename指出SubType是class T中定义的一个类别，因此ptr是一个指向T::SubType型别的指针。如果没有关键字typename，SubType会被当成一个static成员
template <class T>
class MyClass{
    typename T::SubType * ptr;
    ...
};
```


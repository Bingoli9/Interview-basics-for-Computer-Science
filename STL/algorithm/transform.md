## transform

std::transform用于讲指定范围内应用与给定操作，并将结果存储在指定另一个范围内。

```C++
template <class InputIterator, class OutputIterator, class UnaryOperation>
  OutputIterator transform (InputIterator first1, InputIterator last1,
                            OutputIterator result, UnaryOperation op);
	
template <class InputIterator1, class InputIterator2,
          class OutputIterator, class BinaryOperation>
  OutputIterator transform (InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2, OutputIterator result,
                            BinaryOperation binary_op);


```



对于一元操作，将op应用于[first1, last1]范围内的每个元素，并将每个操作返回的值存储在以result开头的范围内。给定的op将被连续调用last1-first1+1次。op可以是函数指针或函数对象或lambda表达式。

如op的一个实现 即将[first1, last1]范围内的每个元素加5，然后依次存储到result中。

```C++
int op_increase(int i) {return (i + 5)};
```


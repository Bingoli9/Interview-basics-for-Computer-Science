## typename

#### Some key conceptions

- qualified name

  qualified name is the name qualifies the namespace

- dependent name

  dependent name relies on the template parameters

```C++
template <class T>
class MyClass {
    int i;
    vector<int> vi;
    vector<int>::iterator vitr;
 
    T t;
    vector<T> vt;
    vector<T>::iterator viter;
};
```

T，vector\<T\> and vector\<T\>::iterator is called dependent name. The first three definition is called non-dependent name.

- class scope

  When accessing the name of a class outside of the class, you can use the class scope operator, such as MyClass::name. There are usually three types of calls: statics data member, static member function, and nested type.

  ```C++
  struct MyClass {
      static int A;
      static int B();
      typedef int C;
  }
  ```

#### Why introduce typename

For following code

```C++
template <class T>
void foo() {
    T::iterator * iter;
    // ...
}
```

iterator can be a nested type in T or static member in T class. If class T doesn't have nested type T, and a global variable named iterator exists, the **T::iterator * iter** can be interpreted as multiplication between two numbers.

To address the problem above, C++ standard introduce the key word **typename**.

So:

**A name used in a template declaration or definition and that is dependent on a template-parameter is assumed not to name a type unless the applicable name lookup finds a type name or the name is qualified by the keyword typename.**




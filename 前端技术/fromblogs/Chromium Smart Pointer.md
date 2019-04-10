## Chromium Smart Pointer

base/memory/

- std::vector\<std::unique_ptr\<>>
- WeakPtr\<>
- scoped_refptr\<>

#### How to select smart pointer

- for unique owner. std::unique_ptr need to point to the object which is not reference count and allocated in heap
- for no owner. Use raw pointer or WeakPtr\<>. WeakPtr\<> can only be destructed by thread which created it. 
- for reference count. Use scoped_refptr\<>

#### how to refer the smart pointer

- Pass std::unique_ptr\<> to function

  ```C++
  // Foo() 拥有 |bar| 的所有权.
    void Foo(std::unique_ptr<Bar> bar);
    
    ...
    std::unique_ptr<Bar> bar_ptr(new Bar());
    Foo(std::move(bar_ptr));          // 调用后，|bar_ptr| 被置为 null.
    Foo(std::unique_ptr<Bar>(new Bar()));  // 临时对象不需要调用std::move()
  ```

- return std::unique\<> from function

  ```C++
  class Base { ... };
    class Derived : public Base { ... };
    
    // Foo 拥有|base|的所有权, 调用方拥有 返回值对象 的所有权
    std::unique_ptr<Base> Foo(std::unique_ptr<Base> base) {
      if (cond) {
        // 转移 |base| 的所有权给调用方
        return base;                           
      }
      
      // 注意这种场景下，方法运行结束时，|base|会被释放掉
      if (cond2) {
        // 临时对象不需要调用std::move()
        return std::unique_ptr<Base>(new Base()));  
      }
      std::unique_ptr<Derived> derived(new Derived());
      // 注意需要使用std::move()，因为|derived|的类型和返回值的类型不同。
      return std::move(derived);
    }
  ```

  


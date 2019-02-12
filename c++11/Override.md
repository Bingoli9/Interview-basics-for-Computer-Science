## Override

Explicity declare which  member function should be overrode.

```C++
class Base {
public:
    virtual void mf1() const;
    virtual void mf2(int x);
    virtual void mf3() &;
    void mf4() const;    // is not declared virtual in Base
};

class Derived: public Base {
public:
    virtual void mf1();        // declared const in Base, but not in Derived.
    virtual void mf2(unsigned int x);    // takes an int in Base, but an unsigned int in Derived
    virtual void mf3() &&;    // is lvalue-qualified in Base, but rvalue-qualified in Derived.
    void mf4() const;        
};
```

In a derived class, overriding inherited from the implementation of a base class member function is under following conditions:

- in the base class, the member funciton is declared virtual
- The return type and exception specification of member functions must be compatible in both base and derived classes
- In base classes and derived classes, member function names, parameter types, convalues, and reference qualifiers must be the same

With so many restrictions, it's easy to get things wrong by mistake

The override keyword in C++11 allows you to explicitly declare in derived classes which member functions need to be overridden and, if not, the compiler will report an error.

```C++
class Derived: public Base {
public:
    virtual void mf1() override;
    virtual void mf2(unsigned int x) override;
    virtual void mf3() && override;
    virtual void mf4() const override;
};
```

```C++
class Derived: public Base {
public:
    virtual void mf1() const override;  // adding "virtual" is OK, but not necessary
    virtual void mf2(int x) override;
    void mf3() & override;
    void mf4() const override; 
};
```


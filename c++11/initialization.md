## initialization
#### aggregate initialization
Initializes an aggregate from braced-init-list


Aggregate initialization initializes aggregates. It is a form of list-initialization (since C++11)

An aggregate is one of the following types:

- array type
- class type (typically, struct or union), that has
    - no private or protected non-static data members
    - no user-declared constructors
    - no user-provided constructors (explicitly defaulted or deleted constructors are allowed)


```C++
T object = {arg1, arg2, ...};	(1)
T object {arg1, arg2, ...};	(2)	(since C++11)
```

#### designed initialization

each designator must name a direct non-static data members of T, and all designators used in the expression must appear in the same order as the data members of T.

```C++
struct A { int x; int y; int z; };
A a{.y = 2, .x = 1}; // error; designator order does not match declaration order
A b{.x = 1, .z = 2}; // ok, b.y initialized to 0
```









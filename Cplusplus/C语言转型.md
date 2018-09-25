## C语言转型

1. const_cast通常被用来将对象的常量型转除，它也是唯一有此能力的C++style转型操作符。
2. dynamic_cast主要用来执行安全向下转型，也就是用来决定某对象是否归属继承体系中的某个类型。他是唯一无法由旧式语法执行的动作，也是唯一可能耗费重大运行成本的转型动作。
3. reinterpret_cast意图执行低级转型，实际动作以及结果可能取决于编译器，它也就表示它不可移植。
4. static_cast用来强迫隐式转换(implicit conversion)，例如将non-const对象转换为const对象，或将int转换为double等等。它也可用来执行上述转换的反向转换。


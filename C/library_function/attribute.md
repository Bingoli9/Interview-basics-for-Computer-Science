## __attribute__((packed))

\_\_attribute\_\_((packer) 的作用就是告诉编译器取消结构在编译过程中的优化对齐，按照实际占用字节数  
进行对齐，是GCC特有语法。这个功能是跟操作系统没有关系，跟编译器有关。  

\_\_attribute\_\_关键字主要是用来在函数或数据声明中设置属性。给函数付给属性的主要目的在于让编译器  
进行优化。函数声明中\_\_attribute\_\_((noreturn))，就是告诉编译器这个函数不会反悔给调用者，  以便编译器在  
优化时去掉不必要的函数返回代码。  

GNU C的一大特色就是__attribute__机制。__attribute__可以设置函数属性（Function Attribute）、变量  
属性（Variable Attribute）和类型属性（Type Attribute）。  

\_\_attribute\_\_((aligned(4))); 4对齐  

\_\_attribute\_\_((packed)) 不对齐 

## JIT

### Hot Spot Compile
java虚拟机执行代码时首先将代码翻译成字节码, 然后解释执行  
使用字节码原因: 若代码只执行一次, 编译代码本质上是浪费时间  
使用机器码原因: 若代码多次执行, 使用字节码将影响性能. 若通过编译把  
字节码翻译成机器码, 可以显著提高执行效率  


在主流商用JVM（HotSpot、J9）中，Java程序一开始是通过解释器（Interpreter）进行解释执行的。  
当JVM发现某个方法或代码块运行特别频繁时，就会把这些代码认定为“热点代码（Hot Spot Code）”，  
然后JVM会把这些代码编译成与本地平台相关的机器码，并进行各种层次的优化，  
完成这个任务的编译器称为：即时编译器（Just In Time Compiler，JIT  









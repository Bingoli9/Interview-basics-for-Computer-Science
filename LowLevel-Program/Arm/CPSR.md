## CPSR
状态寄存器（current program status register）  

CPST低8位（I、F、T和M[4:0]）为控制位，程序无法修改，除非CPU运行  
特权模式，程序可修改控制位  

CPST高4位（N、Z、C、V）为条件标志位，算术或逻辑运算修改这些位  

```C++
N: negative
Z: Zero
C: Carry
V: Overflow
```

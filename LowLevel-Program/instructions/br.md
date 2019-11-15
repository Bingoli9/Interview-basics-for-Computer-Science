## br
```
   tst：逻辑处理指令，用于把一个寄存器的内容和另一个寄存器的内容或立即数进行按位的与运算，并根据运算结果更新CPSR中条件标志位的值。
        当前运算结果为1，则Z=0；当前运算结果为0，则Z=1
　 cmp：算数处理指令，用于把一个寄存器的内容和另一个寄存器的内容或立即数进行减法比较，
        不存储结果，都会更改标志位
　 bne: 数据跳转指令，标志寄存器中Z标志位不等于零时, 跳转到BNE后标签处
　 beq: 数据跳转指令，标志寄存器中Z标志位等于零时, 跳转到BEQ后标签处
```



```
  BNE   Branch if Not Equal
  BVS   Branch if oVerflow Set
  BVC   Branch if oVerflow Clear
  BHI   Branch if HIgher
  BLS   Branch if Lower or the Same
  BPL   Branch if PLus
  BMI   Branch if MInus
  BCS   Branch if Carry Set
  BCC   Branch if Carry Clear
  BGE   Branch if Greater than or Equal
  BGT   Branch if Greater Than
  BLE   Branch if Less than or Equal
  BLT   Branch if Less Than

```

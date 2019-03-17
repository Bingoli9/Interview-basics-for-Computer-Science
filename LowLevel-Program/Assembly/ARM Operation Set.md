## ARM Operation Set

#### ALU State Flag

| N    | Set when the result of the operation was Negative          |
| ---- | ---------------------------------------------------------- |
| Z    | Set when the result of the operation was Zero              |
| C    | Set when the operation result in a Carry(发生进位，或借位) |
| V    | Set when the operation caused oVerflow(操作造成溢出)       |
| Q    | ARM architecture v5E only sticky flag                      |

example

```C++
　　ADD　　r0, r1, r2        ; r0 = r1 + r2, 不更新标志位
　　ADDS　　r0, r1, r2       ; r0 = r1 + r2, 后缀S表示更新标志位
　　ADCSS　　r0, r1, r2      ; If C 标志为1，则执行r0 = r1 + r2, 且更新标志，
　　CMP　　r0, r1            ; CMP指令肯定会更新标志. 
```

#### Addressing Mode

| 种类 | 格式                                   | 模式                     |
| ---- | -------------------------------------- | ------------------------ |
| 1    | [Rn, #±\<offset_12]\>                  | 立即数前索引寻址         |
| 2    | [Rn, ±Rm]                              | 寄存器前索引寻址         |
| 3    | [Rn, Rm, \<shift\>#\<offset_12\>]      | 寄存器位移的前索引寻址   |
| 4    | [Rn, #±\<offset_12\>]!                 | 立即数自动索引寻址       |
| 5    | [Rn, ±Rm]!                             | 寄存器自动索引寻址       |
| 6    | [Rn, Rm, \<shift\<#\<offset_12\>]!     | 寄存器移位的自动索引寻址 |
| 7    | [Rn], #±\<offset_12\>                  | 立即数后索引寻址         |
| 8    | [Rn], ±\<Rm\>                          | 寄存器后索引寻址         |
| 9    | [Rn], ±\<Rm\>, \<shift\>#\<offset_12\> | 带移位的寄存器后索引寻址 |

example

 寄存器移位的前索引寻址

```C++
mov r2, #8
str r1, [r0, r2, lsl #1]　　;将 r1 中的数据存储到地址为 r0 + (r2 << 1)的内存空间中
```

 寄存器后索引寻址

```C++
str r1, [r0], #4　　;将 r1 中的数据存储到地址为 r0 的内存空间中，然后 r0 = r0 + 4
```

 寄存器自动索引寻址　

```C++
str r1, [r0, #4]!　　;将 r1 中的数据存储到 r0 + 4 的内存空间中， 然后 r0 = r0 + 4
```

#### Load/Store指令

| Command | Format                                                    | Description                                                |
| ------- | --------------------------------------------------------- | ---------------------------------------------------------- |
| LDR     | LDR{\<cond\>} \<Rd\>, \<addr_mode\>                       | 用于从内存中将一个32位的字读取到目标寄存器                 |
| STR     | STR{\<cond\>} \<Rd\>,\<addr_mode\>                        | 用于将一个32位的字节数据写入到指令中指定的内存单元         |
| LDM     | LDM{\<cond\>}\<addressing_mode\> \<Rn\>{!}, \<registers\> | 实现数据从连续的内存单元中读取到指令指定的寄存器列表中     |
| STM     | STM{\<cond\>} \<addressing_mode\> \<Rn\>{!}, \<register\> | 实现将指令中寄存器列表里的数值写入到一块连续的内存单元之中 |

Notice:

LDM/STM \<cond\>

|      | 格　　式             | 地址变化格式 |              |
| ---- | -------------------- | ------------ | ------------ |
| 1    | IA(Increment After)  | 后递增方式   | 先存储后增长 |
| 2    | IB(Increment Before) | 先递增方式   | 现增长后存储 |
| 3    | DA(Decrement After)  | 后递减方式   | 先存储后递减 |
| 4    | DB(Decrement Before) | 先递减方式   | 先递减后存储 |

#### Jump指令

| Command | Format               | Description                                                  |
| ------- | -------------------- | ------------------------------------------------------------ |
| B       | B \<lable\>          | 跳转到指定标签处，跳转的时候不会对当前PC值进行保存           |
| BL      | BL \<lable\>         | 跳转到指定标签处，跳转时对当前PC值进行保存                   |
| BX      | BX {\<cond\>} \<Rm\> | 带状态切换的跳转指令,使程序跳转到指令中参数Rm指定的地址进行执行。并将Rm的第0位赋值到CPRS中的T位，bit[31:1]存入PC |

#### 状态寄存器操作指令

| Command | Foramt                                                       | Description                                      |
| ------- | ------------------------------------------------------------ | ------------------------------------------------ |
| MRS     | MPS {cond} Rd, PSR                                           | 用于将CPSR或SPSR的值传送到一个寄存器             |
| MSR     | MSR {cond} PSR_filed, #immed_8r 或者 MSR {cond} PSR_filed, Rm | 用于把一个寄存器的值或一个立即数传送到CPSR或SPSR |

状态寄存器32位被分为4个8位的域，分别为：

|             |        |      |
| ----------- | ------ | ---- |
| bits[31:24] | 条件域 | F    |
| bits[23:16] | 状态域 | S    |
| bits[15:8]  | 预留域 | X    |
| bits[7:0]   | 控制域 | C    |

#### 异常产生指令

| Command | Format                      | Description                      |
| ------- | --------------------------- | -------------------------------- |
| SWI     | SWI {\<cond\>} \<immed_24\> | software interrupt用于产生软中断 |
| BKPT    |                             | 断点中断指令                     |

#### 栈指令

| Command | Description          |
| ------- | -------------------- |
| stmib   | 地址先增而后完成操作 |
| stmia   | 完成操作而后地址递增 |
| stmdb   | 地址先减而后完成操作 |
| stmda   | 完成操作而后地址递减 |
| stmfa   | 满递增堆栈           |
| stmea   | 空递增堆栈           |
| stmfd   | 满递减堆栈           |
| stmed   | 空递减堆栈           |

上述command用于压栈，以下用于出栈

LDMIB、 LDMED

LDMIA， LDMFD

LDMDB， LDMEA

LDMDA， LDMFA

```C++
stmdb sp!, {r0-r12, lr}
```

含义：sp = sp - 4，先压lr，sp = lr（即将lr中的内容放入sp所指的[内存地址](https://www.baidu.com/s?wd=%E5%86%85%E5%AD%98%E5%9C%B0%E5%9D%80&tn=24004469_oem_dg&rsv_dl=gh_pl_sl_csd)）。sp = sp - 4，再压r12，sp = r12。sp = sp - 4，再压r11，sp = r11......sp = sp - 4，最后压r0，sp = r0。 

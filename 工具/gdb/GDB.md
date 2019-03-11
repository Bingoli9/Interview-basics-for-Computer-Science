## GDB

#### 同时给多个函数打断点

使用“rb”命令，如果执行“rb”时不带参数，则表示在所有函数处打一个断点，“rb”后面可以接一个符合正则表达式的参数，用来对符合正则表达式的所有函数打断点

#### 简单函数赃

UT中对函数进行打桩是一件非常麻烦的事情，对于小项目，往往会浪费大量的精力。其实，通过GDB，我们可以变相的实现简单的函数桩，且较为便捷。
基本思路就是在需要打桩的函数上设置断点，待进入函数后，根据对函数的打桩需求，可以分别采取如下措施：

（1）直接返回：用GDB的return命令强制返回即可，如果有返回值，直接跟在return后面即可，如：

return 5

（2）执行函数的部分逻辑：这需要借助GDB的执行路径篡改功能。
“jump <行号>”直接跳至对应的代码行继续执行，也可以用“jump *<地址>”跳转到机器指令地址。

#### 临时数据的构造

在测试一些包含复杂数据类型的代码时，常常需要构造一些复杂结构的临时数据，通常简单易行的办法是直接分配一块临时内存，如：（假设SOME_TYPE是某种复杂数据类型，如typedef的struct、union、enum等）

```C++
set $temp = ({SOME_TYPE *}malloc(sizeof(SOME_TYPE)))
set $temp->some_field = 7
call foo($temp) 
```

#### 常用调式命令

| 命令                                                      | 解释                                                         | 示例                                                         |
| --------------------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| file <文件名>                                             | 加载被调试的可执行程序文件。 因为一般都在被调试程序所在目录下执行GDB，因而文本名不需要带路径。 | (gdb) file gdb-sample                                        |
| r                                                         | Run的简写，运行被调试的程序。 如果此前没有下过断点，则执行完整个程序；如果有断点，则程序暂停在第一个可用断点处。 | (gdb) r                                                      |
| c                                                         | Continue的简写，继续执行被调试程序，直至下一个断点或程序结束。 | (gdb) c                                                      |
| b <行号> b <函数名称> b *<函数名称> b *<代码地址>d [编号] | b: Breakpoint的简写，设置断点。两可以使用“行号”“函数名称”“执行地址”等方式指定断点位置。 其中在函数名称前面加“*”符号表示将断点设置在“由编译器生成的prolog代码处”。如果不了解汇编，可以不予理会此用法。d: Delete breakpoint的简写，删除指定编号的某个断点，或删除所有断点。断点编号从1开始递增。 | (gdb) b 8 (gdb) b main (gdb) b *main (gdb) b *0x804835c(gdb) d |
| s, n                                                      | s: 执行一行源程序代码，如果此行代码中有函数调用，则进入该函数； n: 执行一行源程序代码，此行代码中的函数调用也一并执行。s 相当于其它调试器中的“Step Into (单步跟踪进入)”； n 相当于其它调试器中的“Step Over (单步跟踪)”。这两个命令必须在有源代码调试信息的情况下才可以使用（GCC编译时使用“-g”参数）。 | (gdb) s (gdb) n                                              |
| si, ni                                                    | si命令类似于s命令，ni命令类似于n命令。所不同的是，这两个命令（si/ni）所针对的是汇编指令，而s/n针对的是源代码。 | (gdb) si (gdb) ni                                            |
| p <变量名称>                                              | Print的简写，显示指定变量（临时变量或全局变量）的值。        | (gdb) p i (gdb) p nGlobalVar                                 |
| display ...undisplay <编号>                               | display，设置程序中断后欲显示的数据及其格式。 例如，如果希望每次程序中断后可以看到即将被执行的下一条汇编指令，可以使用命令 “display /i $pc” 其中 $pc 代表当前汇编指令，/i 表示以十六进行显示。当需要关心汇编代码时，此命令相当有用。undispaly，取消先前的display设置，编号从1开始递增。 | (gdb) display /i $pc(gdb) undisplay 1                        |
| i                                                         | Info的简写，用于显示各类信息，详情请查阅“help i”。           | (gdb) i r                                                    |
| q                                                         | Quit的简写，退出GDB调试环境。                                | (gdb) q                                                      |
| help [命令名称]                                           | GDB帮助命令，提供对GDB名种命令的解释说明。 如果指定了“命令名称”参数，则显示该命令的详细说明；如果没有指定参数，则分类显示所有GDB命令，供用户进一步浏览和查询。 | (gdb) help display                                           |

#### Condition break point

```C++
>commands 22                        

->if (vport->port_no!=4)

->bt

->c

->else

->bt

->end
```

```C++
>b  10 if index == 3        
```

#### Save all break points

```C++
(gdb)save breakpoints file-name-to-save
```

#### input all break point

```C++
(gdb)source file-name-to-save
```

#### Switch windows

```C++
help layout
layout src
layout asm
winheight src + 10
```

#### Kernel Dubugging

```C++
查看指定内核模块的内存加载地址

#cat /proc/modules |grep tun                                                                            

为指定模块加载symbol文件

>add-symbol-file /home/dawei/nzuta/nzuta.ko  0xffffffffa0423000  
```


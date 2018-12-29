## gdb段错误

#### Resolve the core dump

check the setting of core dump

```C++
ulimit -c
0
cat /proc/sys/kernel/core_pattern
core
```

change the setting of core dump pattern

```C++
ulimit -c unlimited
mkdir /var/cores
echo "/var/cores/core.%e.%p" > /proc/sys/kernel/core_pattern
```

#### Start GDB for Execute Target and Core Dump File

#### Backtrace

```C++
bt
```

Using bt to trace stack information

If most of symbols parsed failed, try to use extern tools to restore it

#### Disassembling

```C++
disas
```

#### Check Register

```C+
i f (info registers)
```

#### Memory Map

```C++
i proc m (info proc mappings)
```

#### Break Points

先回到反汇编

```c++
   0x00007f0a37aac401 <+289>:   mov    0x20cb68(%rip),%rax        # 0x7f0a37cb8f70
   0x00007f0a37aac408 <+296>:   mov    (%rax),%rsi
   0x00007f0a37aac40b <+299>:   xor    %eax,%eax
=> 0x00007f0a37aac40d <+301>:   mov    0x10(%rsi),%rdi

```

看这四条指令：好像是从栈中取东西放到 %rax，然后解引用 %rax 到 %rsi，再将 %eax 置零（ xor 是一个优化，替换掉移动 0 的动作），最后将 %rsi 解引用再加一个偏移，不过我们知道 %rsi 是零。这几条指令用来访问数据结构。 可能 %rax 会很有趣，但是它已经被前面的指令置零，所以我们在核心转储文件的寄存器里看不到它的值。

#### Step Debugging

跳到下一条指令（si，stepi的简写），然后检查寄存器：

```C++
(gdb) si
0x00007ffff34ad408 in doupdate () from /lib/x86_64-linux-gnu/libncursesw.so.5
(gdb) i r
rax            0x7ffff3e8f948   140737285519688
rbx            0xaea060 11444320
rcx            0xae72a0 11432608
rdx            0xa403d0 10748880
rsi            0x7ffff7ea8e10   140737352732176
rdi            0xa403d0 10748880
rbp            0x7ffff3e8fb10   0x7ffff3e8fb10 <SP>
rsp            0x7fffffffd390   0x7fffffffd390
r8             0x7ffff36ba3e0   140737277305824
r9             0x0  0
r10            0x8  8
r11            0x202    514
r12            0x0  0
r13            0x0  0
r14            0x7ffff3e8fb10   140737285520144
r15            0xa403d0 10748880
rip            0x7ffff34ad408   0x7ffff34ad408 <doupdate+296>
eflags         0x202    [ IF ]
cs             0x33 51
ss             0x2b 43
ds             0x0  0
es             0x0  0
fs             0x0  0
gs             0x0  0
(gdb) p/a 0x7ffff3e8f948
$1 = 0x7ffff3e8f948 <cur_term>
```

又一条线索。所以我们解引用的空指针好像是一个叫 “cur_term” 的符号（p/a 是 print/a 的简写，这里 “/a” 指以地址的形式）。

#### TraceBack

和之前一样我在 doupdate 下断点，一旦触发，我就启动 recording，然后继续运行程序直到崩溃。Recording 会增加相当大的开销，所以我不想在主函数里就将它打开。

```C++
(gdb) b doupdate
Function "doupdate" not defined.
Make breakpoint pending on future shared library load? (y or [n]) y
Breakpoint 1 (doupdate) pending.
(gdb) r cachetop.py
Starting program: /usr/bin/python cachetop.py
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
warning: JITed object file architecture unknown is not compatible with target architecture i386:x86-64.
 
Breakpoint 1, 0x00007ffff34ad2e0 in doupdate () from /lib/x86_64-linux-gnu/libncursesw.so.5
(gdb) record
(gdb) c
Continuing.
 
Program received signal SIGSEGV, Segmentation fault.
0x00007ffff34ad40d in doupdate () from /lib/x86_64-linux-gnu/libncursesw.so.5

```

Here, we can use reverse-stepi to trace back the register state.

```C++
reverse-stepi
```



#### Debug Info


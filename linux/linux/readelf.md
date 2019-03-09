## readelf

readelf elf文件格式分析  

####ELF文件
executable and linking format。

#### ELF文件类型
- 可重定位的对象文件(Relocatable file)
	由汇编器汇编生成的 .o 文件

- 可执行的对象文件(Executable file)
	可执行应用程序
- 可被共享的对象文件(Shared object file)
	动态库文件，也即 .so 文件

#### 字段说明
```C++
.text section 里装载了可执行代码；
.data section 里面装载了被初始化的数据；
.bss section 里面装载了未被初始化的数据；
以 .rec 打头的 sections 里面装载了重定位条目；
.symtab 或者 .dynsym section 里面装载了符号信息；
.strtab 或者 .dynstr section 里面装载了字符串信息；
```


想知道一个应用程序的可运行的架构平台:

```C++
$readelf -h main| grep Machine
-h选项将显示文件头的概要信息，从里面可以看到，有很多有用的信息：

$readelf -h main
ELF Header:
Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
Class:                             ELF64
Data:                              2 s complement, little endian
Version:                           1 (current)
OS/ABI:                            UNIX - System V
ABI Version:                       0
Type:                              EXEC (Executable file)
Machine:                           Advanced Micro Devices X86-64
Version:                           0x1
Entry point address:               0x400790
Start of program headers:          64 (bytes into file)
Start of section headers:          5224 (bytes into file)
Flags:                             0x0
Size of this header:               64 (bytes)
Size of program headers:           56 (bytes)
Number of program headers:         8
Size of section headers:           64 (bytes)
Number of section headers:         29
Section header string table index: 26
```

```C++
一个编译好的应用程序，想知道其编译时是否使用了-g选项（加入调试信息）:
$readelf -S main| grep debug
用-S选项是显示所有段信息；如果编译时使用了-g选项，则会有debug段;
```

```C++
查看.o文件是否编入了调试信息（编译的时候是否加了-g):
$readelf -S Shpos.o | grep debug
```

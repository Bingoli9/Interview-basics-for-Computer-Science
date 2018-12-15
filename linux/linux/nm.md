##nm
nm 命令显示关于制定FIle中符号的信息，文件可以对象文件，可执行文件或对象文件库。  
如果文件没有包含符号信息，nm命令报告该情况，但不解释为出错条件。  

```C++
$nm myProgrammer
08049f28 d _DYNAMIC
08049ff4 d _GLOBAL_OFFSET_TABLE_
080484dc R _IO_stdin_used
         w _Jv_RegisterClasses
08049f18 d __CTOR_END__
08049f14 d __CTOR_LIST__
08049f20 D __DTOR_END__
08049f1c d __DTOR_LIST__
080485e0 r __FRAME_END__
08049f24 d __JCR_END__
08049f24 d __JCR_LIST__
0804a014 A __bss_start
0804a00c D __data_start
08048490 t __do_global_ctors_aux
08048360 t __do_global_dtors_aux
0804a010 D __dso_handle
         w __gmon_start__
08048482 T __i686.get_pc_thunk.bx
08049f14 d __init_array_end
08049f14 d __init_array_start
08048480 T __libc_csu_fini
08048410 T __libc_csu_init
         U __libc_start_main@@GLIBC_2.0
0804a014 A _edata
0804a01c A _end
080484bc T _fini
080484d8 R _fp_hw
080482b4 T _init
08048330 T _start
0804a014 b completed.6086
0804a00c W data_start
0804a018 b dtor_idx.6088
080483c0 t frame_dummy
080483e4 T main
U printf@@GLIBC_2.0
```

这些包含可执行代码的段称为正文段。  
同样地，数据段包含了不可执行的信息或数据。  
另一种类型的段，称为 BSS 段，它包含以符号数据开头的块。  
对于 nm 命令列出的每个符号，它们的值使用十六进制来表示（缺省行为），并且在该符号前面加上了一个表示符号类型的编码字符。  

可以将目标文件中所包含的不同的部分划分为段。  
段可以包含可执行代码、符号名称、初始数据值和许多其他类型的数据。  
有关这些类型的数据的详细信息，可以阅读 UNIX 中 nm 的 man 页面，其中按照该命令输出中的字符编码分别对每种类型进行了描述。  

####符号说明
```C++
A 该符号的值是绝对的，在以后的链接过程中，不允许进行改变。这样的符号值，常常出现在中断向量表中，例如用符号来表示各个中断向量函数在中断向量表中的位置。
B 该符号的值出现在非初始化数据段(bss)中。例如，在一个文件中定义全局static int test。则该符号test的类型为b，位于bss section中。其值表示该符号在bss段中的偏移。一般而言，bss段分配于RAM中。
C 该符号为common。common symbol是未初始话数据段。该符号没有包含于一个普通section中。只有在链接过程中才进行分配。符号的值表示该符号需要的字节数。例如在一个c文件中，定义int test，并且该符号在别的地方会被引用，则该符号类型即为C。否则其类型为B。
D 该符号位于初始化数据段中。一般来说，分配到data section中。
例如：定义全局int baud_table[5] = {9600, 19200, 38400, 57600, 115200}，会分配到初始化数据段中。G 该符号也位于初始化数据段中。主要用于small object提高访问small data object的一种方式。
I 该符号是对另一个符号的间接引用。
N 该符号是一个debugging符号。
R 该符号位于只读数据区。
例如定义全局const int test[] = {123, 123};则test就是一个只读数据区的符号。
值得注意的是，如果在一个函数中定义const char *test = “abc”, const char test_int = 3。使用nm都不会得到符号信息，但是字符串”abc”分配于只读存储器中，test在rodata section中，大小为4。
S 符号位于非初始化数据区，用于small object。
T 该符号位于代码区text section。
U 该符号在当前文件中是未定义的，即该符号的定义在别的文件中。
例如，当前文件调用另一个文件中定义的函数，在这个被调用的函数在当前就是未定义的；但是在定义它的文件中类型是T。但是对于全局变量来说，在定义它的文件中，其符号类型为C，在使用它的文件中，其类型为U。
V 该符号是一个weak object。
W The symbol is a weak symbol that has not been specifically tagged as a weak object symbol.
? 该符号类型没有定义
```





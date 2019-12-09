## GDB Coredump

```
A segmentation fault (often shortened to segfault) is a particular error condition that can occur during the operation of computer software. In short, a segmentation fault occurs when a program attempts to access a memory location that it is not allowed to access, or attempts to access a memory location in a way that is not allowed (e.g., attempts to write to a read-only location, or to overwrite part of the operating system). Systems based on processors like the Motorola 68000 tend to refer to these events as Address or Bus errors.  Segmentation is one approach to memory management and protection in the operating system. It has been superseded by paging for most purposes, but much of the terminology of segmentation is still used, "segmentation fault" being an example. Some operating systems still have segmentation at some logical level although paging is used as the main memory management policy.  On Unix-like operating systems, a process that accesses invalid memory receives the SIGSEGV signal. On Microsoft Windows, a process that accesses invalid memory receives the STATUS_ACCESS_VIOLATION exception.
```

### dmesg

Dmesg can display information stored in the kernel when the application crashes.As shown below, the dmesg command allows you to see the program name where the segment error occurred, the memory address that caused the segment error to occur, the instruction pointer address, the stack pointer address, the error code, the cause of the error, and so on.

### -g

Using the source code of the GCC compiler with the -g parameter allows the generated binaries to be packed with useful information that can be used for GDB debugging

### nm

Use the nm command to list the symbol table in the binary file, including symbol addresses, symbol types, symbol names, and so on, to help locate where a segment error occurred


### ldd

Use the LDD command to look at the Shared link library dependencies of binaries, including the library name and starting address, to determine whether the segment error occurred in your own program or in a dependent Shared library.

### gcc + gdb

```C++
gcc -g -o segfault3 segfault3.c

gdb ./segfault3
```

### core + gdb

```C++
ulimit -c 1024   //To generate the core file
   
./segfault3

gdb ./segfault3 ./core
```

### objdump + dmsg

Using **dmsg** command to get the address that occurs the coredump error.

```C++
objdump -d ./segfault3 > segfault2Dump
```

Search the segfault2Dump file.

According to the assembly language, find the source code.

### catchsegv

The **catchsegv** command is designed to catch segment errors by loading a pre-written library (/lib/ libsegfault.so) through the PRELOAD mechanism of the dynamic loader (ld-linux.so) to catch fault breaking error messages.

```C++
catchsegv ./segfault3 
```




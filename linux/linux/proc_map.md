## proc/self/map
原文章: https://blog.csdn.net/sunao2002002/article/details/84132505
```C++
/proc/[pid]/maps
 A file containing the currently mapped memory regions and their access permissions.
 See mmap(2) for some further information about memory mappings.

The format of the file is:

address           perms offset  dev   inode       pathname
00400000-00452000 r-xp 00000000 08:02 173521      /usr/bin/dbus-daemon
00651000-00652000 r--p 00051000 08:02 173521      /usr/bin/dbus-daemon
00652000-00655000 rw-p 00052000 08:02 173521      /usr/bin/dbus-daemon
00e03000-00e24000 rw-p 00000000 00:00 0           [heap]
00e24000-011f7000 rw-p 00000000 00:00 0           [heap]
...
35b1800000-35b1820000 r-xp 00000000 08:02 135522  /usr/lib64/ld-2.15.so
35b1a1f000-35b1a20000 r--p 0001f000 08:02 135522  /usr/lib64/ld-2.15.so
35b1a20000-35b1a21000 rw-p 00020000 08:02 135522  /usr/lib64/ld-2.15.so
35b1a21000-35b1a22000 rw-p 00000000 00:00 0
35b1c00000-35b1dac000 r-xp 00000000 08:02 135870  /usr/lib64/libc-2.15.so
35b1dac000-35b1fac000 ---p 001ac000 08:02 135870  /usr/lib64/libc-2.15.so
35b1fac000-35b1fb0000 r--p 001ac000 08:02 135870  /usr/lib64/libc-2.15.so
35b1fb0000-35b1fb2000 rw-p 001b0000 08:02 135870  /usr/lib64/libc-2.15.so
...
f2c6ff8c000-7f2c7078c000 rw-p 00000000 00:00 0    [stack:986]
...
7fffb2c0d000-7fffb2c2e000 rw-p 00000000 00:00 0   [stack]
7fffb2d48000-7fffb2d49000 r-xp 00000000 00:00 0   [vdso]

The address field is the address space in the process that the mapping occupies.  
address部分显示的是该段映射的虚拟地址。

The perms field is a set of permissions:

r = read
w = write
x = execute
s = shared
p = private (copy on write)
权限分为rwxsp，r可读、w可写、x可执行、s共享、p私有或者（写时拷贝）。

The  offset  field is the offset into the file/whatever; dev is the device (major:minor); inode is the inode on that device.
0 indicates that no inode is associated with the memory region, as would be the case with BSS (uninitialized data).
offset是指该段映射在文件/其它设备上的偏移量。inode是指文件或者设备的inode节点，0表示没有inode与该段内存关联。


The pathname field will usually be the file that is backing the mapping.
For ELF files, you can easily coordinate with the offset field by looking at the Offset field in the ELF program headers (readelf -l).

路径名是与该段内存关联的文件路径。对于ELF文件，可以通过realelf-l在offset字段和ELF文件头部OFFSET字段同步。

There are additional helpful pseudo-paths:

[stack] The initial process's (also known as the main thread's) stack.
主线程/进程堆栈
[stack:<tid>] (since Linux 3.4) A thread's stack (where the <tid> is a thread ID).  It corresponds to the /proc/[pid]/task/[tid]/ path.
线程堆栈。
[vdso] The virtual dynamically linked shared object.
内核虚拟动态映射对象
[heap] The process's heap.
进程的堆空间。

If  the  pathname  field is blank, this is an anonymous mapping as obtained via the mmap(2) function.
There is no easy way to coordinate this back to a process's source, short of running it through gdb(1), strace(1), or similar.
如果pathname为空，那么是通过mmap函数进行的匿名映射。没有简单的方法获得该字段，需要查看代码，或者gdb、strace等类似的方法。

Under Linux 2.0 there is no field giving pathname
```

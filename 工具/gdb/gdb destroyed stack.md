## gdb destroyed stack

```C++
$ gdb IMActivityServer.symbol core.32530
(gdb) bt
#0  0x0000000000a6951a in ?? ()
#1  0x00000000018c6db8 in ?? ()
#2  0x8f127f1911ab2800 in ?? ()
#3  0x00000000018c6d00 in ?? ()
#4  0x0000000400000004 in ?? ()
#5  0x00000000018c6d88 in ?? ()
#6  0x00000000006ba9bf in ?? ()
#7  0x00000000018a4400 in ?? ()
#8  0x8f127f1911ab2800 in ?? ()
#9  0x00000000018c6d00 in ?? ()
#10 0x00007f518b789010 in ?? ()
#11 0x00000000018c6d00 in ?? ()
#12 0x0000000000693166 in ?? ()
#13 0x0000000000000000 in ?? ()
```

Can't see any information, log can't see anything, suspected stack corruption

Adds stack protection, inserts protection code with the compilation parameter **-fstack-protector-all** for all functions, compiles  and then checks the crash dump with symbol again

```C++
$ gdb IMActivityServer.symbol core.32530
(gdb) bt
#0  0x00007f08a95d7118 in ?? () from /lib64/libgcc_s.so.1
#1  0x00007f08a95d8019 in _Unwind_Backtrace () from /lib64/libgcc_s.so.1
#2  0x00007f08a93110c6 in backtrace () from /lib64/libc.so.6
#3  0x00007f08a927c334 in __libc_message () from /lib64/libc.so.6
#4  0x00007f08a9314a77 in __fortify_fail () from /lib64/libc.so.6
#5  0x00007f08a9314a40 in __stack_chk_fail () from /lib64/libc.so.6
#6  0x00000000006909a9 in ActivityService::cmdMsgParse (this=<optimized out>, ptNullCmd=<optimized out>, 
    nCmdLen=<optimized out>) at ActivityServer.cpp:930
#7  0x00007f08a75ae1e8 in ?? ()
#8  0x00007f0818000978 in ?? ()
#9  0x00007f0818000a08 in ?? ()
#10 0x00007f0818000970 in ?? ()
#11 0x0000000000000000 in ?? ()
```

Notice:

If the core dump is conditional, we need to check out variables to locate the problem. Usually we can print detail  log information. But if the program is very complicate, we need to insert break points to get more detail.

 

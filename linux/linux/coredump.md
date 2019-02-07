## core dump
### dmesg

dmesg can list all drive loaded in kernel   
and it can also be used to record system core dump error  

### addr2line
Every executable program has debug info, and one of the most  
important information is the correspond relations in line number and  
compile code which is called Line Number Table.  

example:  
addr2line -e test1 400506

### nm
nm can used to list the symbol table, including symbol address, symbol type, and  
symbol name etc. It can help to locate the core dump address.  
example:  
nm bin/Test | grep 0904f5  
```C++
0804f560 T nwGtpv1uMsgAddIeTV1
0804f5a0 T nwGtpv1uMsgAddIeTV2
0804f5e0 T nwGtpv1uMsgAddIeTV4
0804f500 T nwGtpv1uMsgGetTpduHandle
0804f530 T nwGtpv1uMsgGetTpduLength
```

### objdump
objdump can disassembling the executable file and redirect it into file.  





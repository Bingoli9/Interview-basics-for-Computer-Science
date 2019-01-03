## tail
tail 命令用途是依照要求将指定的文件的最后部分输出到标准设备  
通常是终端，通俗俩将，就是把某个文件的最后几行显示到终端上，  
文档有更新的话，tail会自己主动刷新， 确保看到最新的文档内容。  

```C++
tail -n 20 filename
tail -r -n 10 filename
\tail -f filename
```
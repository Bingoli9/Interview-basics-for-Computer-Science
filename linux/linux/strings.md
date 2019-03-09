## strings

strings命令在对象文件或二进制文件中查找可打印的字符串。  
字符串是4个或更多可打印字符的任意序列，以换行符或空字符结束  
strings命令对识别随机对象文件很有用  
```C++
strings [ -a ] [ - ] [ -o ] [ -t Format ] [ -n Number ] [ -Number ] [ file ... ]
```

example:
```C++
列出ls中所有的ASCII文本：
strings /bin/ls
```

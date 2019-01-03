## BASH_SOURCE
BASH_SOURCE[0] 等价于BASH_SOURCE， 取得当前执行的shell文件所在的路径以及文件名  

如/home/abc/test.sh 内容如下
```C++
#!/bin/sh
echo "${BASH_SOURCE[0]}"
echo "${BASH_SOURCE]}"
echo "$( dirname "${BASH_SOURCE[0]}" )"
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo $DIR
```
总之：  
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )" 得到shell脚本文件所在完整路径（绝对路径）及文件名（无论source,sh,.三种调用方式），且不改变shell的当前目录。



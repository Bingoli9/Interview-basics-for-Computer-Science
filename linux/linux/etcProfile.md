## /etc/profile

```C++
1./etc/profile , /etc/profile.d ，~/.bashrc, ~/.bash_file,这几个文件的区别是啥，可能很多新人，很疑惑。即使很多配置一些软件环境变量的人也是很疑惑

   ~/.bashrc, ~/.bash_file这两个看到～这个符合，应该明白，这是宿主目录下的，即里面的环境变量也叫shell变量，是局部的，只对特定的shell有效，修改过别忘了source 命令一下。

   /etc/profile , /etc/profile.d，前面的是文件，后面一看也就明白.d表示目录， /etc/profile里面的变量是全局的，对所有用户的shell有效。

2. 我们每当在终端输入命令，系统会有响应，最重要的就是搜索路径啦，可以通过echo $PATH看到，系统所以命令的搜索路径，以：符合分开。

    当我们下载一个软件，如果我们希望不加入路径就能启动该程序，如在shell中任意位置输入eclipse，即启动程序，我们就可以把eclipse程序的可执行程序的路径加入到PATH中即可。

    其实我们还可以有另一种方法，请看如下代码

# The default umask is now handled by pam_umask.
# See pam_umask(8) and /etc/login.defs.


if [ -d /etc/profile.d ]; then              # 判断/etc/profile.d 是不是一个目录
  for i in /etc/profile.d/*.sh; do       #如果是一个目录，到该目录下，取出每一个shell程序
    if [ -r $i ]; then                             #如果该shell可以执行

      . $i                                               # 则执行它
    fi
  done
  unset i
fi

```

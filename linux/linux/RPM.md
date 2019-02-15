## rpm

```C++
-i, --install                     install package(s) 
-v, --verbose                     provide more detailed output 
-h, --hash                        print hash marks as package installs (good with -v) 
-e, --erase                       erase (uninstall) package 
-U, --upgrade=<packagefile>+      upgrade package(s) －
-replacepkge                    无论软件包是否已被安装，都强行安装软件包 -
-test                            安装测试，并不实际安装
--nodeps                          忽略软件包的依赖关系强行安装 
--force                           忽略软件包及文件的冲突
Query options (with -q or --query): 
-a, --all                         query/verify all packages
-p, --package                     query/verify a package file 
-l, --list                        list files in package 
-d, --docfiles                    list all documentation files 
-f, --file                        query/verify package(s) owning file
```


## Samba

将远程服务器目录映射到本机共享目录上

#### 相关配置文件和一些命令工具

```C++
/etc/samba/smb.conf
/etc/init.d/smb
```

```C++
srevice smb status
service smb start
service smb stop
chkconfig --level 35 smb on //设置开机启动
```



#### smb config file

```C++
[global]　　　　　　　　　　　　　　　　　　　　							//设置samba服整体环境
workgroup = WORKGROUP　　　　　　　　　　  								//设置工作组名称
server string = Samba Server Version %v                //服务器说明

[laiGei]　　　　　　　　　　　　　　　　　　   //共享目录的名称

comment = Public stuff　　　　　　　　　　　　   //注释说明　
path = /usr/local/laige　　　　　　　　   　　　　  //共享目录的路径
public = yes　　　　　　　　　　　　　　　　　  //是yes/否no公开共享，若为否则进行身份验证(只有当security = share 时此项才起作用)
writeable = yes　　　　　　　　　　　　　　　　//是yes/否no不以只读方式共享当与read only发生冲突时，无视read only
browseable = yes　　　　　　　　　　　　　　   //是yes/否no在浏览资源中显示共享目录，若为否则必须指定共享路径才能存取
guest ok = yes　　　　　　　　　　　　　　　　//是yes/否no公开共享，若为否则进行身份验证(只有当security = share 时此项才起作用)
```



```C++
//Ubuntu 服务端
useradd $username  //添加用户
smbpasswd -a $username  //添加用户和密码
// Mac local 端
 chown liqining /home && mount -t smbfs //liqining:password@ip/home /home
```
## Android Multi-Process Communication

#### Activity

```java
Intent callIntent = new  Intent(Intent.ACTION_CALL, Uri.parse("tel:12345678" );  
startActivity(callIntent);
```

#### Content Provider

通过文件或SqlLite数据库存储数据



#### 广播



#### AIDL Service

要实现跨进程通信，需要借助AIDL(Android Interface Definition Language)。Android中的跨进程服务其实是采用C/S的[架构](http://cpro.baidu.com/cpro/ui/uijs.php?adclass=0&app_id=0&c=news&cf=1001&ch=0&di=128&fv=20&is_app=0&jk=e1c94d8eb3072940&k=%BC%DC%B9%B9&k0=%BC%DC%B9%B9&kdi0=0&luki=1&mcpm=0&n=10&p=baidu&q=65035100_cpr&rb=0&rs=1&seller_id=1&sid=402907b38e4dc9e1&ssp2=1&stid=9&t=tpclicked3_hc&td=1836545&tu=u1836545&u=http%3A%2F%2Fwww.bubuko.com%2Finfodetail-458771.html&urlid=0)，因而AIDL的目的就是实现通信接口。
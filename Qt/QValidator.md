 ## QValidator

QValidator类提供一种验证输入是否有效的方法。

```c++
验证的结果有三种状态：
enum State {
    Invalid,             //验证通不过
    Intermediate,   //输入未完成，不确定是否能通过验证
    Acceptable   //验证通过
```

 QValidator提供validate和fixup的公有方法：


```c++
virtual State validate(QString &, int &) const = 0;
virtual void fixup(QString &) const;
 这两个函数都是虚函数，派生类可以重写它。
```


     QValidator::validate()是验证的过程，返回结果是State。每当输入有变化时调用此方法。
    
     QValidator::fixedup()是当验证通不过时，通过调用这个函数修复错误。


    

     若要实现一个自定义的验证类，需要从QValidator下派生一个类，并选择性重写validate和fixedup方法。


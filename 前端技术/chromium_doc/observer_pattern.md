
## chromium 观察者模式

<center>
    @<img src = "8VtYAlH"/>
</center>

Subject 需要自己实现AddObserver和RemoveObserver。定义号通知的类，加上ObserverList\<\>对象

#### 通知

```C++
FOR_EACH_OBSERVER(ObserverType, observer_list, func)
```




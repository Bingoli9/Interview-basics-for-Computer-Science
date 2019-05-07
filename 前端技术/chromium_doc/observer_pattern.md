
## chromium 观察者模式

<center>
    @<img src = "8VtYAlH"/>
</center>

Subject 需要自己实现AddObserver和RemoveObserver。定义号通知的类，加上ObserverList\<\>对象

#### 通知

```C++
FOR_EACH_OBSERVER(ObserverType, observer_list, func)
```


#### 通过观察者模式写测试代码

```c++
class DownloadItemCreateObserver : public DownloadManager::Observer {

public:
explict DownloadItemCreateObserver(DownloadManager* manager)
: manager_(manager) {
    manager->AddObserver(this);
}

~DownLoadItemCreteateObserver() override {
    if (manager_) 
        manager_ -> RemoveObserver(this);
}
}
```








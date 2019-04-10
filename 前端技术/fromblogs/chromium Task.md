## chromium Task

提供模版类base::Callback\<>,该类有Run函数。作为函数指针泛型，由base::Bind产生

#### example1

```C++
void ReadToString(const std::string& filename, const base::Callback<void(const std::string&)>& on_read);
 
void DisplayString(const std::string& result) {
  LOG(INFO) << result;
}
 
void SomeFunc(const std::string& file) {
  ReadToString(file, base::Bind(&DisplayString));
};
```



#### PostTask & PostDelayedTask

```C++
void MessageLoop::PostTask(
    const tracked_objects::Location& from_here, const base::Closure& task)
其中，
typedef Callback<void(void)> Closure;
```

```C++
void WriteToFile(const std::string& filename, const std::string& data);
BrowserThread::PostTask(BrowserThread::FILE, FROM_HERE,
                        base::Bind(&WriteToFile, "foo.txt", "hello world!"));
```



#### 类成员函数Task

类对象通常引用计数

```C++
class MyObject : public base::RefCountedThreadSafe<MyObject> {
 public:
  void DoSomething(const std::string16& name) {
    thread_->message_loop()->PostTask(
       FROM_HERE, base::Bind(&MyObject::DoSomethingOnAnotherThread, <strong>this</strong>, name));
  }
 
  void DoSomethingOnAnotherThread(const std::string16& name) {
    ...
  }
 private:
  // Always good form to make the destructor private so that only RefCountedThreadSafe can access it.
  // This avoids bugs with double deletes.
  friend class base::RefCountedThreadSafe<MyObject>;
 
  ~MyObject();
  Thread* thread_;
};
```

注意：base::bind中参数会被复制到内部存储结构

#### base::WeakPtr

base::WeakPtr和base::WeakPtrFactory用于保证object的生命周期之外对应的调用不会发生。当base::WeakPtr设置为无效时候，禁止task的执行。当factory释放时候，所有base::WeakPtr都会在内部设置为无效位，任何绑定task均无效。

注意：task被发往同一个线程时候才有效

```C++
class MyObject {
 public:
  MyObject() : weak_factory_(this) {}
 
  void DoSomething() {
    const int kDelayMS = 100;
    MessageLoop::current()->PostDelayedTask(FROM_HERE,
        base::Bind(&MyObject::DoSomethingLater, weak_factory_.GetWeakPtr()),
        kDelayMS);
  }
 
  void DoSomethingLater() {
    ...
  }
 
 private:
  base::WeakPtrFactory<MyObject> weak_factory_;
};
```

#### 可取消任务

weakPtr不是线程安全的。跨线程适合用CancelableTaskTracker。可以使用任务返回的id来取消另一个线程的任务

```C++
class UserInputHandler : public base::RefCountedThreadSafe<UserInputHandler> {
  // Runs on UI thread.
  void OnUserInput(Input input) {
    CancelPreviousTask();
    DBResult* result = new DBResult();
    task_id_ = tracker_->PostTaskAndReply(
        BrowserThread::GetMessageLoopProxyForThread(BrowserThread::DB),
        FROM_HERE,
        base::Bind(&LookupHistoryOnDBThread, this, input, result),
        base::Bind(&ShowHistoryOnUIThread, this, base::Owned(result)));
  }
 
  void CancelPreviousTask() {
    tracker_->TryCancel(task_id_);
  }
 
  ...
 
 private:
  CancelableTaskTracker tracker_;  // Cancels all pending tasks while destruction.
  CancelableTaskTracker::TaskId task_id_;
  ...
};

```

任务由于是在另一个线程执行，不能保证一定会被取消。但是可以保证不会crash吧

    当我们使用TryCancel（）时候，
    
       1. 如果task和reply都没有开始执行，则都会取消
    
       2. 如果task正在执行或者已经执行完，reply会取消
    
       3. 如果reply正在执行或者已经执行完，无操作

---------------------

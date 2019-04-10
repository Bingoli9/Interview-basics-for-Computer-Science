## chromium base

- cantainer

  Located in container folder

  - STL container
  - hash_map hash_set
  - LinkedList 
  - MRUCache

- smart pointer

  Located in memory folder

  - WeakPrt
  - scoped_refptr

- callback

- Thread

  - base::Thread
  - base::ThreadLocalPointer
  - base::MessageLoop
  - base::Lock
  - base::WaitableEvent

- string

  - std::string

- file

  Located in root directory and in files folder

  - base::File

- timer

  - base::Timer

- log and debug

  Located in debug and profile folder

- system monitor

  Located in system_monitor, power_monitor and memory

- Android

  - android adpter

- tools



### LinkedList

base::LinkedList use memory pool technique to reduce memory allocation operation.

```C++
class MyNodeType : public LinkNode<MyNodeType> {
    ...
};

LinkedList<MyNodeType> list;

LinkNode<MyNodeType>* n1 = ...;
LinkNode<MyNodeType>* n2 = ...;
LinkNode<MyNodeType>* n3 = ...;

list.Append(n1);
list.Append(n3);
n2->InsertBefore(n3);

for (LinkNode<MyNodeType>* node = list.head();
    node != list.end();
    node = node->next()) {
    MyNodeType* value = node->value();
    ...
}
```

### MRU

most recently used. Like STL::map container, but has maximum capticity.

- MRUCache
- OwingMRUCache
- HashingMRUCache

### String

Located in strings folder

- string.empty()
- 字符串常量使用char[], 比如const char kFoo[] = "foo"
- 在循环的inner loop里面，避免临时std::string对象的创建
- Other methods

### Log and Debug

##### tracer

Chromium provides Tracing mechanism for debuging. 

For Android, Chromium privides Android Systrace. To use Android Systrace, we need to open the Chromium Tracing, and use Android Systrace to capture the tracing output.

To add tracing method, use following code

```C++
TRACE_EVENT0("android_webview", "BrowserViewRender::OnDrawHardware")
```

More detail to see trace_event.h

##### backtrace stack

base::debug::StackTrace provides function call stack printing. StackTrace will store current stack data when create, and print them on the console.



### System monitor

Use MemoryPressureListener interface

```C++
void OnMemoryPressure(MemoryPressureLevel memory_pressure_level) {
       ...
    }
    // Start listening.
    MemoryPressureListener* my_listener =
        new MemoryPressureListener(base::Bind(&OnMemoryPressure));
    ...
    // Stop listening.
    delete my_listener;
```

### LazyInstance

LazyInstance delaye creating global static object, it's advantage:

- pre-allocate memory
- thread safe
- delay creating object

### Singleton

```C++
// In your header:
   template <typename T> struct DefaultSingletonTraits;
   class FooClass {
    public:
     static FooClass* GetInstance();
     void Bar() { ... }
    private:
     FooClass() { ... }
     friend struct DefaultSingletonTraits<FooClass>;
     DISALLOW_COPY_AND_ASSIGN(FooClass);
   };
// In your source file:
  FooClass* FooClass::GetInstance() {
    return Singleton<FooClass>::get();
  }
// And to call methods on FooClass:
   FooClass::GetInstance()->Bar();
```

### AutoReset

base::AutoReset will store variable old data and set new data for it. When life cycle ends and begin destructing, it will restore the variable value.

```C++
{
    base::AutoReset<bool> frame_resetter(&viewport_clip_valid_for_dcheck_,
                                         true);
    layer_tree_host_->SetNeedsRedrawRect(clip_);
    layer_tree_host_->Composite(gfx::FrameTime::Now());
  }
ObserverList，ObserverListThreadSafe
```

### ObserverList

Helper for observer pattern. It's thread safe.
## mojo

### 消息管道（Message Pipes）
消息管道两端handle是进程范围内唯一的  
消息管道两端可以不同进程或者同一进程  
chromium mojo::MessagePipe封装消息管道  

### Mojom Bindings
Mojom是IDL（Interface Define Language）  
给定Mojom文件，可以生成不同语言的接口，接口用于IPC通信  

### C++ Binding API
#### mojo::InterfacePtr\<T\>
mojo::InterfacePtr\<T\>是service T的代理，它绑定到消息管道endpoint  
```C++
  mojo::MessagePipe pipe;
  mojo::InterfacePtr<frob::Frobinator> frobinator;
  frobinator.Bind(
      mojo::InterfacePtrInfo<frob::Frobinator>(pipe.handle0.Pass(), 0u));
```
调用frobinator->Frobinator()，在消息管道的另一端可以读取数据  

#### mojo::InterfaceRequest\<T\>

mojo::InterfaceRequest可以看作消息管道接收端容器，读取消息管道数据  
```C++
mojo::MessagePipe pipe;

mojo::InterfacePtr<frob::Frobinator> frobinator;
frobinator.Bind(
    mojo::InterfacePtrInfo<frob::Frobinator>(pipe.handle0.Pass(), 0u));

mojo::InterfaceRequest<frob::Frobinator> frobinator_request;
frobinator_request.Bind(pipe.handle1.Pass());
```

### mojo::GetProxy\<T\>
mojo::GetProxy\<T\>用于创建新的消息管道  
```C++
mojo::InterfacePtr<frob::Frobinator> frobinator;
mojo::InterfaceRequest<frob::Frobinator> frobinator_request =
mojo::GetProxy(&frobinator);
```

### mojo::Binding\<T\>
绑定服务T，消息管道的另一端写入的数据将会被服务T读取  
```C++
#include "components/frob/public/interfaces/frobinator.mojom.h"
#include "third_party/mojo/src/mojo/public/cpp/bindings/binding.h"
#include "third_party/mojo/src/mojo/public/cpp/bindings/interface_request.h"

class FrobinatorImpl : public frob::Frobinator {
 public:
  FrobinatorImpl(mojo::InterfaceRequest<frob::Frobinator> request)
      : binding_(this, request.Pass()) {}
  ~FrobinatorImpl() override {}

 private:
  // frob::Frobinator:
  void Frobinate() override { /* ... */ }

  mojo::Binding<frob::Frobinator> binding_;
};
```
```C++
// Fun fact: The bindings generator emits a type alias like this for every
// interface type. frob::FrobinatorPtr is an InterfacePtr<frob::Frobinator>.
frob::FrobinatorPtr frobinator;
scoped_ptr<FrobinatorImpl> impl(
    new FrobinatorImpl(mojo::GetProxy(&frobinator)));
frobinator->Frobinate();
```
### mojo::StrongBinding\<T\>
mojo::StrongBinding\<T\>获取T的ownsership  
实例T将会被销毁当消息管道关闭的时候  

EDK: Mojo Embedder Development Kit
### Mojo通信原理
1. message buffer分配，并且填充写入的数据
2. 通知EDK将消息写入消息管道
3. 通知EDK来源不在mojo线程，EDK将跳转到mojo线程
4. EDK将消息写入管道。如果消息管道两端在同一个进程，消息传递由memcpy实现  
如果不在同一个进程，消息传递经过真正的管道  ‘
5. 在消息管道的另一端，在mojo线程的EDK被唤醒
6. EDK获取消息
7. 如果消息管道的另一端不在mojo线程，EDK将进入mojo线程
8. 消息管道另一端通过Binding\<T\>，获取消息并调用处理函数


### Mojo Example

```C++



```








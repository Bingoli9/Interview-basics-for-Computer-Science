## Mojo

#### Message pipe

A pair of endpoints. Each endpoint has a queeu of incoming message, and writing a message at one endpoint effectively enqueues that message on the other endpoint. 

#### mojom file

一个mojom file是消息类型的集合，一个消息类型对应一个协议

通过 mojom接口和消息 pipeline，interfacePtr可以用来发送message，Binding 可以用来接受接口消息

Binding端需要绑定mojom 接口的实现来处理收到的消息。 



#### Mojo在choromium的应用

假设需要从render frame发送ping message到render frame host, 步骤如下：

##### Defining the interface

新建.mojom 文件， 定义以下接口

```C++
// src/example/public/mojom/ping_responder.mojom
module example.mojom;

interface PingResponder {
  // Receives a "Ping" and responds with a random integer.
  Ping() => (int32 random);
};
```

通过gni工具生成c++ bindings

```C++
# src/example/public/mojom/BUILD.gn
import("//mojo/public/tools/bindings/mojom.gni")
mojom("mojom") {
  sources = [ "ping_responder.mojom" ]
}
```

##### creating the Pipe

```C++
example::mojom::PingResponderPtr ping_responder;
example::mojom::PingResponderRequest request =
    mojo::MakeRequest(&ping_responder);
```

mojo::MakeRequest 接受PingRespongderPtr作为参数创建messagePipe




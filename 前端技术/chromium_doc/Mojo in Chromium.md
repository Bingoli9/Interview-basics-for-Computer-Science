## Mojo in Chromium

The Mojo system API provides a small suite of low-level IPC primitives: message pipes, data pipes, and shared buffers. On top of this API, we've built higher-level bindings APIs to simplifiy messaging.

That's, IPC

#### Binding to Pipes

```C++
typedef mojo::InterfaceRequest<mojom::Frobinator> mojom::FrobinatorRequest
```

```C++
// src/components/frob/frobinator_impl.cc

#include "components/frob/public/interfaces/frobinator.mojom.h"
#include "mojo/public/cpp/bindings/binding.h"
#include "mojo/public/cpp/bindings/interface_request.h"

namespace frob {

class FrobinatorImpl : public mojom::Frobinator {
 public:
  FrobinatorImpl(mojom::FrobinatorRequest request)
      : binding_(this, std::move(request)) {}
  ~FrobinatorImpl() override {}

  // mojom::Frobinator:
  void Frobinate() override { DLOG(INFO) << "I can't stop frobinating!"; }

 private:
  mojo::Binding<mojom::Frobinator> binding_;
};

}  // namespace frob
```

##### mojo::binding\<T> 

binds one end of a message pipe to an implementation of a service.

##### InterfaceRequest\<T> & InterfacePtr\<T>

```C++
mojom::FrobinatiorPtr proxy;
mojom::FrobinatiorPtrRequest request = mojo::GetProxy(&proxy)
```

This creates a new message pipe with one end owned by proxy and the other end owned by request. It has the nice property of attaching common type information to each end of the pipe.

InterfacePtr\<T> scopes a message pipe endpoint as well, but it alse internally implements every method on T by serializeing a correspongding message and writing it to the pipe.

```C++
frob:mojom::FrobinatorPtr frobinator;
frob::FrobinatorImple impl(GetProxy(&frobinator));

//Tada!
frobinator->Frobinate();
```

<center>
  <img src = "/Users/liqining/Desktop/20180918213527758.png"/>
</center>

#### Responding to Requests

A common idiom in Chromium IPC is to keep track of IPC requests with some kind of opaque identifier (i.e. an integer *request ID*) so that you can later respond to a specific request using some nominally related message in the other direction.

```C++
class FrobinatorImpl : public mojom::Frobinator {
 public:
  // ...

  // mojom::Frobinator:
  void Frobinate() override { /* ... */ }
  void GetFrobinationLevels(const GetFrobinationLevelsCallback& callback) {
    callback.Run(1, 42);
  }
};

```

When the service implementation runs `callback`, the response arguments are serialized and sent back over the pipe. The proxy on the other end knows how to read this response and will in turn dispatch it to a callback on that end:

```C++
void ShowLevels(int min, int max) {
  DLOG(INFO) << "Frobinator min=" << min << " max=" << max;
}

// ...

  mojom::FrobinatorPtr frobinator;
  FrobinatorImpl impl(GetProxy(&frobinator));

  frobinator->GetFrobinatorLevels(base::Bind(&ShowLevels));
```


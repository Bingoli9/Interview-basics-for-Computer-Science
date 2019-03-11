## Proxy Pattern

In some cases where a client does not want or cannot directly refer to an object, an indirect reference can be made through a third party called a proxy.Proxy objects can mediate between the client and the target object and can be used to remove content and services that the client cannot see or to add additional services that the client needs.

The pattern motivation of the proxy pattern is to implement the operation on the real object by introducing a new object (such as a small picture and a remote proxy object) or to use the new image as a surrogate for the real object.

Proxy Pattern: provides an agent to an object, and the Proxy object controls the reference to the original object. It is a kind of object structure mode.

![Proxy](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/Proxy.jpg?raw=true)

![seq_Proxy](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/seq_Proxy.jpg?raw=true)

```C++
#include <iostream>
#include "RealSubject.h"
#include "Proxy.h"

using namespace std;

int main(int argc, char *argv[])
{
	Proxy proxy;
	proxy.request();
	
	return 0;
}
```

```C++
///////////////////////////////////////////////////////////
//  Proxy.h
//  Implementation of the Class Proxy
//  Created on:      07-十月-2014 16:57:54
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_56011290_0413_40c6_9132_63EE89B023FD__INCLUDED_)
#define EA_56011290_0413_40c6_9132_63EE89B023FD__INCLUDED_

#include "RealSubject.h"
#include "Subject.h"

class Proxy : public Subject
{

public:
	Proxy();
	virtual ~Proxy();

	void request();

private:
	void afterRequest();
	void preRequest();	
	RealSubject *m_pRealSubject;

};
#endif // !defined(EA_56011290_0413_40c6_9132_63EE89B023FD__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  Proxy.cpp
//  Implementation of the Class Proxy
//  Created on:      07-十月-2014 16:57:54
//  Original author: colin
///////////////////////////////////////////////////////////

#include "Proxy.h"
#include <iostream>
using namespace std;


Proxy::Proxy(){
	//有人觉得 RealSubject对象的创建应该是在main中实现；我认为RealSubject应该
	//对用户是透明的，用户所面对的接口都是通过代理的；这样才是真正的代理； 
	m_pRealSubject = new RealSubject();
}

Proxy::~Proxy(){
	delete m_pRealSubject;
}

void Proxy::afterRequest(){
	cout << "Proxy::afterRequest" << endl;
}


void Proxy::preRequest(){
	cout << "Proxy::preRequest" << endl;
}


void Proxy::request(){
	preRequest();
	m_pRealSubject->request();
	afterRequest();
}
```




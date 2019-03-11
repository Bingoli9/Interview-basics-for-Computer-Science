## Flyweight Pattern

Object-oriented technology can solve some flexibility or extensibility problems well, but in many cases it needs to increase the number of classes and objects in the system.When the number of objects is too large, it will lead to high cost of running, resulting in performance degradation and other problems.

Sharing model is to solve this kind of problems and the birth.Sharing meta-patterns enable reuse of the same or similar objects through sharing techniques.

Can share the same content in the flyweight pattern known as the internal State (IntrinsicState), and those who need to set up the external environment cannot share content called external State (Extrinsic State), due to distinguish between the internal and external State, so you can set different external State makes the same object can have some different characteristics, and the same internal State can be Shared.

Factory mode is common in share mode, and a share factory needs to be created to maintain a Flyweight Pool for storing share objects with the same internal state.

Shared in the Shared meta-mode is the internal state of the Shared meta-object, which needs to be set by the environment.In practice, there is a limited amount of internal state that can be Shared, so Shared meta-objects are generally designed to be smaller objects that contain less internal state, also known as fine-grained objects.The purpose of the Shared element pattern is to reuse a large number of fine-grained objects using Shared techniques.



Flyweight Pattern: the use of sharing technology effectively supports the reuse of a large number of fine-grained objects.The system only USES a small number of objects, and these objects are very similar, the state change is very small, can achieve multiple reuse of objects.Since shared-element mode requires that objects that can be Shared must be fine-grained objects, it is also known as lightweight mode. It is an object structure mode.

![Flyweight](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/Flyweight.jpg?raw=true)

![seq_Flyweight](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/seq_Flyweight.jpg?raw=true)

```C++
#include <iostream>
#include "ConcreteFlyweight.h"
#include "FlyweightFactory.h"
#include "Flyweight.h"
using namespace std;

int main(int argc, char *argv[])
{
	FlyweightFactory factory;
	Flyweight * fw = factory.getFlyweight("one");
	fw->operation();
	
	Flyweight * fw2 = factory.getFlyweight("two");
	fw2->operation();
	//aready exist in pool
	Flyweight * fw3 = factory.getFlyweight("one");
	fw3->operation();
	return 0;
}
```

```C++
///////////////////////////////////////////////////////////
//  FlyweightFactory.cpp
//  Implementation of the Class FlyweightFactory
//  Created on:      06-十月-2014 20:10:42
//  Original author: colin
///////////////////////////////////////////////////////////

#include "FlyweightFactory.h"
#include "ConcreteFlyweight.h"
#include <iostream>
using namespace std;

FlyweightFactory::FlyweightFactory(){

}



FlyweightFactory::~FlyweightFactory(){

}

Flyweight* FlyweightFactory::getFlyweight(string str){
	map<string,Flyweight*>::iterator itr = m_mpFlyweight.find(str);
	if(itr == m_mpFlyweight.end())
	{
		Flyweight * fw = new ConcreteFlyweight(str);
		m_mpFlyweight.insert(make_pair(str,fw));
		return fw;	
	}
	else
	{
		cout << "aready in the pool,use the exist one:" << endl;
		return itr->second;
	}		
}
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteFlyweight.h
//  Implementation of the Class ConcreteFlyweight
//  Created on:      06-十月-2014 20:10:42
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_C0AF438E_96E4_46f1_ADEC_308EF16E11D1__INCLUDED_)
#define EA_C0AF438E_96E4_46f1_ADEC_308EF16E11D1__INCLUDED_

#include "Flyweight.h"
#include <string>
using namespace std;

class ConcreteFlyweight : public Flyweight
{

public:
	ConcreteFlyweight(string str);
	virtual ~ConcreteFlyweight();

	virtual void operation();

private:
	string intrinsicState;

};
#endif // !defined(EA_C0AF438E_96E4_46f1_ADEC_308EF16E11D1__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteFlyweight.cpp
//  Implementation of the Class ConcreteFlyweight
//  Created on:      06-十月-2014 20:10:42
//  Original author: colin
///////////////////////////////////////////////////////////

#include "ConcreteFlyweight.h"
#include <iostream>
using namespace std;


ConcreteFlyweight::ConcreteFlyweight(string str){
	intrinsicState = str;
}

ConcreteFlyweight::~ConcreteFlyweight(){

}

void ConcreteFlyweight::operation(){
	cout << "Flyweight[" << intrinsicState << "] do operation." << endl; 
}
```


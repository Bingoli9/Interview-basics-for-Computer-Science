## Adapter Pattern

Adapter Pattern: the transformation of one interface into another as desired by the client. The Adapter Pattern allows classes whose interfaces are incompatible to work together, alias wrappers.The adapter pattern can be either a class structure pattern or an object structure pattern.

![Adapter_classModel](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/Adapter_classModel.jpg?raw=true)

![seq_Adapter](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/seq_Adapter.jpg?raw=true)

```C++
#include <iostream>
#include "Adapter.h"
#include "Adaptee.h"
#include "Target.h"

using namespace std;

int main(int argc, char *argv[])
{
	Adaptee * adaptee  = new Adaptee();
	Target * tar = new Adapter(adaptee);
	tar->request();
	
	return 0;
}
```

```C++
///////////////////////////////////////////////////////////
//  Adapter.h
//  Implementation of the Class Adapter
//  Created on:      03-十月-2014 17:32:00
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_BD766D47_0C69_4131_B7B9_21DF78B1E80D__INCLUDED_)
#define EA_BD766D47_0C69_4131_B7B9_21DF78B1E80D__INCLUDED_

#include "Target.h"
#include "Adaptee.h"

class Adapter : public Target
{

public:
	Adapter(Adaptee *adaptee);
	virtual ~Adapter();

	virtual void request();

private:
	Adaptee* m_pAdaptee;

};
#endif // !defined(EA_BD766D47_0C69_4131_B7B9_21DF78B1E80D__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  Adapter.cpp
//  Implementation of the Class Adapter
//  Created on:      03-十月-2014 17:32:00
//  Original author: colin
///////////////////////////////////////////////////////////

#include "Adapter.h"

Adapter::Adapter(Adaptee * adaptee){
	m_pAdaptee =  adaptee;
}

Adapter::~Adapter(){

}

void Adapter::request(){
	m_pAdaptee->specificRequest();
}
```

```C++
///////////////////////////////////////////////////////////
//  Adaptee.h
//  Implementation of the Class Adaptee
//  Created on:      03-十月-2014 17:32:00
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_826E6B4F_12BE_4609_A0A3_95BD5E657D36__INCLUDED_)
#define EA_826E6B4F_12BE_4609_A0A3_95BD5E657D36__INCLUDED_

class Adaptee
{

public:
	Adaptee();
	virtual ~Adaptee();

	void specificRequest();

};
#endif // !defined(EA_826E6B4F_12BE_4609_A0A3_95BD5E657D36__INCLUDED_)
```


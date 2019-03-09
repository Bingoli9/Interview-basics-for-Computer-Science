## Observer Mode

Establish an object-to-object dependency that automatically notifies other objects when an object changes, and other objects react accordingly. Here, observed object is called observation object, and the notified object  is called observer.  An observed object can correspond to more than one observer, and no correlation between the observer. We add and remove the observer according to tht need, and it makes the system more easy to expand. This is the motivation of the observer mode.

![Obeserver](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/Obeserver.jpg?raw=true)

![seq_Obeserver](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/seq_Obeserver.jpg?raw=true)

```C++
#include <iostream>
#include "Subject.h"
#include "Obeserver.h"
#include "ConcreteObeserver.h"
#include "ConcreteSubject.h"

using namespace std;

int main(int argc, char *argv[])
{
	Subject * subject = new ConcreteSubject();
	Obeserver * objA = new ConcreteObeserver("A");
	Obeserver * objB = new ConcreteObeserver("B");
	subject->attach(objA);
	subject->attach(objB);
	
	subject->setState(1);
	subject->notify();
	
	cout << "--------------------" << endl;
	subject->detach(objB);
	subject->setState(2);
	subject->notify();
	
	delete subject;
	delete objA;
	delete objB;
		
	return 0;
}
```

```C++
///////////////////////////////////////////////////////////
//  Subject.h
//  Implementation of the Class Subject
//  Created on:      07-十月-2014 23:00:10
//  Original author: cl
///////////////////////////////////////////////////////////

#if !defined(EA_61998456_1B61_49f4_B3EA_9D28EEBC9649__INCLUDED_)
#define EA_61998456_1B61_49f4_B3EA_9D28EEBC9649__INCLUDED_

#include "Obeserver.h"
#include <vector>
using namespace std;

class Subject
{

public:
	Subject();
	virtual ~Subject();
	Obeserver *m_Obeserver;

	void attach(Obeserver * pObeserver);
	void detach(Obeserver * pObeserver);
	void notify();
		
	virtual int getState() = 0;
	virtual void setState(int i)= 0;
	
private:
	vector<Obeserver*> m_vtObj;

};
#endif // !defined(EA_61998456_1B61_49f4_B3EA_9D28EEBC9649__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  Subject.cpp
//  Implementation of the Class Subject
//  Created on:      07-十月-2014 23:00:10
//  Original author: cl
///////////////////////////////////////////////////////////

#include "Subject.h"

Subject::Subject(){

}

Subject::~Subject(){

}

void Subject::attach(Obeserver * pObeserver){
	m_vtObj.push_back(pObeserver);
}

void Subject::detach(Obeserver * pObeserver){
	for(vector<Obeserver*>::iterator itr = m_vtObj.begin();
		itr != m_vtObj.end(); itr++)
	{
		if(*itr == pObeserver)
		{
			m_vtObj.erase(itr);
			return;
		}			
	}
}

void Subject::notify(){
	for(vector<Obeserver*>::iterator itr = m_vtObj.begin();
		itr != m_vtObj.end();
	 	itr++)
	{	
		(*itr)->update(this);		
	}
}
```

```C++
///////////////////////////////////////////////////////////
//  Obeserver.h
//  Implementation of the Class Obeserver
//  Created on:      07-十月-2014 23:00:10
//  Original author: cl
///////////////////////////////////////////////////////////

#if !defined(EA_2C7362B2_0B22_4168_8690_F9C7B76C343F__INCLUDED_)
#define EA_2C7362B2_0B22_4168_8690_F9C7B76C343F__INCLUDED_

class Subject;

class Obeserver
{

public:
	Obeserver();
	virtual ~Obeserver();
	virtual void update(Subject * sub) = 0;
};
#endif // !defined(EA_2C7362B2_0B22_4168_8690_F9C7B76C343F__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteObeserver.h
//  Implementation of the Class ConcreteObeserver
//  Created on:      07-十月-2014 23:00:09
//  Original author: cl
///////////////////////////////////////////////////////////

#if !defined(EA_7B020534_BFEA_4c9e_8E4C_34DCE001E9B1__INCLUDED_)
#define EA_7B020534_BFEA_4c9e_8E4C_34DCE001E9B1__INCLUDED_
#include "Obeserver.h"
#include <string>
using namespace std;

class ConcreteObeserver : public Obeserver
{

public:
	ConcreteObeserver(string name);
	virtual ~ConcreteObeserver();
	virtual void update(Subject * sub);

private:
	string m_objName;
	int m_obeserverState;
};
#endif // !defined(EA_7B020534_BFEA_4c9e_8E4C_34DCE001E9B1__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteObeserver.cpp
//  Implementation of the Class ConcreteObeserver
//  Created on:      07-十月-2014 23:00:09
//  Original author: cl
///////////////////////////////////////////////////////////

#include "ConcreteObeserver.h"
#include <iostream>
#include <vector>
#include "Subject.h"
using namespace std;

ConcreteObeserver::ConcreteObeserver(string name){
	m_objName = name;
}

ConcreteObeserver::~ConcreteObeserver(){

}

void ConcreteObeserver::update(Subject * sub){
	m_obeserverState = sub->getState();
	cout << "update oberserver[" << m_objName << "] state:" << m_obeserverState << endl;
}
```

### Advantages of the observer pattern

The observer pattern can separate the presentation layer from the data logic layer, define a stable message update mechanism, and abstract the update interface, so that a variety of different presentation layers can act as concrete observers.

The observer pattern establishes an abstract coupling between the observed object and the observer.

Observer mode supports broadcast communication.

The observer pattern conforms to the "open closed principle".

### The MVC pattern

The MVC pattern is an architectural pattern that consists of three roles: Model, View, and Controller.The observer pattern can be used to implement the MVC pattern. The observed object in the observer pattern is the Model in the MVC pattern, while the observer is the View in the MVC pattern, and the Controller ACTS as an Mediator between them.When the data in the model layer changes, the view layer automatically changes its display content.

## State Mode

In many cases, an object's behavior depends on one or more dynamically changing properties, such as states, such objects are called stateful objects, and such object states are taken out of a predefined set of values.When such an object interacts with external events, its internal state changes, resulting in changes in the behavior of the system.

A state diagram can be used in UML to describe changes in an object's state.

![State](https://github.com/leekeiling/Design%20Mode/blob/master/pics/State.jpg?raw=true)

![seq_State](https://github.com/leekeiling/Design%20Mode/blob/master/pics/seq_State.jpg?raw=true)

```C++
#include <iostream>
#include "Context.h"
#include "ConcreteStateA.h"
#include "ConcreteStateB.h"

using namespace std;

int main(int argc, char *argv[])
{
	char a = '0';
	if('0' == a)
		cout << "yes" << endl;
	else
		cout << "no" << endl;
	
	Context * c = new Context();
	c->request();
	c->request();
	c->request();

	delete c;
	return 0;
}
```

```C++
///////////////////////////////////////////////////////////
//  Context.h
//  Implementation of the Class Context
//  Created on:      09-十月-2014 17:20:59
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_F245CF81_2A68_4461_B039_2B901BD5A126__INCLUDED_)
#define EA_F245CF81_2A68_4461_B039_2B901BD5A126__INCLUDED_

#include "State.h"

class Context
{

public:
	Context();
	virtual ~Context();

	void changeState(State * st);
	void request();

private:
	State *m_pState;
};
#endif // !defined(EA_F245CF81_2A68_4461_B039_2B901BD5A126__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  Context.cpp
//  Implementation of the Class Context
//  Created on:      09-十月-2014 17:20:59
//  Original author: colin
///////////////////////////////////////////////////////////

#include "Context.h"
#include "ConcreteStateA.h"

Context::Context(){
	//default is a
	m_pState = ConcreteStateA::Instance();
}

Context::~Context(){
}

void Context::changeState(State * st){
	m_pState = st;
}

void Context::request(){
	m_pState->handle(this);
}
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteStateA.h
//  Implementation of the Class ConcreteStateA
//  Created on:      09-十月-2014 17:20:58
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_84158F08_E96A_4bdb_89A1_4BE2E633C3EE__INCLUDED_)
#define EA_84158F08_E96A_4bdb_89A1_4BE2E633C3EE__INCLUDED_

#include "State.h"

class ConcreteStateA : public State
{

public:
	virtual ~ConcreteStateA();
	
	static State * Instance();
	
	virtual void handle(Context * c);

private:
	ConcreteStateA();
	static State * m_pState;
};
#endif // !defined(EA_84158F08_E96A_4bdb_89A1_4BE2E633C3EE__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteStateA.cpp
//  Implementation of the Class ConcreteStateA
//  Created on:      09-十月-2014 17:20:58
//  Original author: colin
///////////////////////////////////////////////////////////

#include "ConcreteStateA.h"
#include "ConcreteStateB.h"
#include "Context.h"
#include <iostream>
using namespace std;

State * ConcreteStateA::m_pState = NULL;
ConcreteStateA::ConcreteStateA(){
}

ConcreteStateA::~ConcreteStateA(){
}

State * ConcreteStateA::Instance()
{
	if ( NULL == m_pState)
	{
		m_pState = new ConcreteStateA();
	}
	return m_pState;
}

void ConcreteStateA::handle(Context * c){
	cout << "doing something in State A.\n done,change state to B" << endl;
	c->changeState(ConcreteStateB::Instance());
}
```

State patterns describe how an object's state changes and how the object behaves differently in each state.

The key to the state pattern is the introduction of an abstract class that specifically represents the state of an object. This class is called the abstract state class, and each concrete state class of an object inherits this class and implements the behavior of different states in different concrete state classes, including transitions between various states.

It is necessary to understand the role of environment class and abstract state class in the state pattern structure:

An environment class is actually an object that has State, and it can sometimes act as a State Manager to switch State within the environment class.

Abstract state classes can be abstract classes or interfaces. Different state classes are different subclasses that inherit from this parent class. The generation of state classes is due to the existence of multiple states in the environment class.Therefore, the behavior of different objects can be extracted separately and encapsulated in specific state classes, so that the environment class object can change its behavior when its internal state changes. The object seems to modify its class, but actually it is realized by switching to different specific state classes.Since the environment class can be set to any specific state class, it is programmed for the abstract state class. When the program is running, the object of any specific state class can be set to the environment class, so that the environment class can change its internal state and change its behavior.

### Advantages of state patterns

Encapsulates the transformation rules.

Enumerate possible states. You need to determine the type of state before enumerating the states.

Putting all the behavior associated with a state into a class and easily adding new states can change the behavior of an object simply by changing its state.

Allows state transition logic to be combined with a state object, rather than a single giant conditional statement block.

You can reduce the number of objects in the system by having multiple environment objects share a single state object.

### The disadvantage of state patterns

The use of state patterns inevitably increases the number of system classes and objects.

The structure and implementation of the state pattern are complex, and improper use will lead to confusion of program structure and code.

The "open and close principle" is not well supported by the state mode. For the state mode that can switch state, adding new state class needs to modify the source code that is responsible for the state transition, otherwise it cannot switch to the new state.Modifying the behavior of a state class also requires modifying the source code of the corresponding class.










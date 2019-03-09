## Mediator Mode

In the design scheme of direct chat between users and users, there is a strong correlation between user objects, which will lead to the following problems in the system:

System structure is complex: there are a large number of interconnections and invocations between objects, and if one object changes, you need to keep track of all other objects associated with that object and process them appropriately.

Poor reusability of objects: since an object has a strong association with other objects, it is difficult for an object to be reused by another system or module without the support of other objects. These objects are more like an indivisible whole, and their responsibilities are more confused.

Low system scalability: adding a new object requires adding a reference to the original related object, and adding a new reference relationship also requires adjusting the original object. The system has a high degree of coupling, the object operation is not flexible, and the scalability is poor.

In the object-oriented software design and development process, according to the "single responsibility principle", we should try to refine the object, so that it is only responsible for or present a single responsibility.

For a module, it may be composed of many objects, and there may be mutual references between these objects. In order to reduce the complex reference relationship between two objects and make it a loosely coupled system, we need to use the intermediary pattern, which is the pattern motivation of the intermediary pattern.

![Mediator](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/Mediator.jpg?raw=true)
![seq_Mediator](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/seq_Mediator.jpg?raw=true)

```C++
#include <iostream>
#include "ConcreteColleagueA.h"
#include "ConcreteMediator.h"
#include "ConcreteColleagueB.h"

using namespace std;

int main(int argc, char *argv[])
{
	ConcreteColleagueA * pa = new ConcreteColleagueA();
	ConcreteColleagueB * pb = new ConcreteColleagueB();
	ConcreteMediator * pm = new ConcreteMediator();
	pm->registered(1,pa);
	pm->registered(2,pb);
	
	// sendmsg from a to b
	pa->sendmsg(2,"hello,i am a");
	// sendmsg from b to a
	pb->sendmsg(1,"hello,i am b");
	
	delete pa,pb,pm;
	return 0;
}
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteMediator.h
//  Implementation of the Class ConcreteMediator
//  Created on:      07-十月-2014 21:30:47
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_8CECE546_61DD_456f_A3E7_D98BC078D8E8__INCLUDED_)
#define EA_8CECE546_61DD_456f_A3E7_D98BC078D8E8__INCLUDED_

#include "ConcreteColleagueB.h"
#include "Mediator.h"
#include "ConcreteColleagueA.h"
#include <map>
using namespace std;
class ConcreteMediator : public Mediator
{

public:
	ConcreteMediator();
	virtual ~ConcreteMediator();

	virtual void operation(int nWho,string str);
	virtual void registered(int nWho, Colleague * aColleague);
private:
	map<int,Colleague*> m_mpColleague;
};
#endif // !defined(EA_8CECE546_61DD_456f_A3E7_D98BC078D8E8__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteMediator.cpp
//  Implementation of the Class ConcreteMediator
//  Created on:      07-十月-2014 21:30:48
//  Original author: colin
///////////////////////////////////////////////////////////

#include "ConcreteMediator.h"
#include <map>
#include <iostream>
using namespace std;

ConcreteMediator::ConcreteMediator(){

}

ConcreteMediator::~ConcreteMediator(){

}

void ConcreteMediator::operation(int nWho,string str){
	map<int,Colleague*>::const_iterator itr = m_mpColleague.find(nWho);
	if(itr == m_mpColleague.end())
	{
		cout << "not found this colleague!" << endl;
		return;
	}
	
	Colleague* pc = itr->second;
	pc->receivemsg(str);
}


void ConcreteMediator::registered(int nWho,Colleague * aColleague){
	map<int,Colleague*>::const_iterator itr = m_mpColleague.find(nWho);
	if(itr == m_mpColleague.end())
	{
		m_mpColleague.insert(make_pair(nWho,aColleague));
		//同时将中介类暴露给colleague 
		aColleague->setMediator(this);
	}
}
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteColleagueA.h
//  Implementation of the Class ConcreteColleagueA
//  Created on:      07-十月-2014 21:30:47
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_79979DD4_1E73_46db_A635_E3F516ACCE0A__INCLUDED_)
#define EA_79979DD4_1E73_46db_A635_E3F516ACCE0A__INCLUDED_

#include "Colleague.h"

class ConcreteColleagueA : public Colleague
{

public:
	ConcreteColleagueA();
	virtual ~ConcreteColleagueA();

	virtual void sendmsg(int toWho,string str);
	virtual void receivemsg(string str);

};
#endif // !defined(EA_79979DD4_1E73_46db_A635_E3F516ACCE0A__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteColleagueA.cpp
//  Implementation of the Class ConcreteColleagueA
//  Created on:      07-十月-2014 21:30:47
//  Original author: colin
///////////////////////////////////////////////////////////

#include "ConcreteColleagueA.h"
#include <iostream>
using namespace std;

ConcreteColleagueA::ConcreteColleagueA(){
}

ConcreteColleagueA::~ConcreteColleagueA(){
}

void ConcreteColleagueA::sendmsg(int toWho,string str){
	cout << "send msg from colleagueA,to:" << toWho << endl;
	m_pMediator->operation(toWho,str);
}

void ConcreteColleagueA::receivemsg(string str){
	cout << "ConcreteColleagueA reveivemsg:" << str <<endl;
}
```

The mediator pattern can dramatically reduce the number of relationships between objects.

An intermediary has two responsibilities:

Relaying (structural) : through the relaying provided by the intermediary, each colleague object no longer needs to refer to other colleagues explicitly. When it is necessary to communicate with other colleagues, it can just go through the intermediary.The intermediary role belongs to the structural support of the intermediary.

Coordinating role (behavioral) : The intermediary can further capsulate the relationship between colleagues. Colleagues can coordinately interact with the intermediary and there's no need to indicate concrete operations. The intermediary further  processes the requests by colleagues with coordinating logic capsulated in the intermediary.

### Advantages of the intermediary model

Simplified interaction between objects.

Decouple colleagues.

Reduce subclass generation.

Can simplify the design and implementation of each colleague class.

### Disadvantages of the intermediary model

The inclusion of details of interactions between colleagues in a concrete mediator class can lead to a very complex concrete mediator class that makes the system difficult to maintain.


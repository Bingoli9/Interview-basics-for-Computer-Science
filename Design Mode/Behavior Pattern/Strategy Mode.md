## Strategy Mode

To complete a task, there are often many different ways, each way is called a strategy, we can choose different strategies according to the different environment or conditions to complete the task.

In software development, a similar situation is often encountered, there are multiple ways to achieve a certain function, at this time, a design pattern can be used to make the system can choose a solution flexibly, but also can easily add new solutions.

In software system, there are many algorithms can achieve a certain function, such as search, sort, a commonly used method is hard-coded (Hard Coding) in a class, such as the need to provide a variety of search algorithm, these algorithms can be written in a class, in the class to provide multiple methods, each method corresponds to a specific search algorithms;Of course, these search algorithms can also be encapsulated in a unified method, through the if...The else...And other conditional statements to select.We can call these two implementation methods as hard coding. If we need to add a new search algorithm, we need to modify the source code of the encapsulated algorithm class.Change the search algorithm, also need to modify the client call code.This algorithm class encapsulates a large number of search algorithms, this class code will be more complex, more difficult to maintain.

In addition to providing specialized lookup algorithm classes, you can also include the algorithm code directly in the client program, which is even less desirable. This will make the client program large and difficult to maintain, and the problem will become more serious if there are a large number of alternative algorithms.

In order to solve these problems, you can define some independent classes to encapsulate different algorithms, each class encapsulates a specific algorithm, in this case, each class we can call it a wrapper algorithm Strategy (Strategy), in order to ensure the consistency of these strategies, the Strategy of tend to use an abstract class to do the algorithm, the definition of each algorithm and specific Strategy corresponds to a specific class.



### Strategy Pattern 

defines a series of algorithms, encapsulates each algorithm, and makes them interchangeable.A Policy pattern, also known as a Policy pattern, allows an algorithm to change independently of the customers that use it.

A policy pattern is an object behavior pattern.

![Strategy](https://github.com/leekeiling/Design%20Mode/blob/master/pics/Strategy.jpg?raw=true)

![seq_Strategy](https://github.com/leekeiling/Design%20Mode/blob/master/pics/seq_Strategy.jpg?raw=true)

```C++
#include <iostream>
#include "Context.h"
#include "ConcreteStrategyA.h"
#include "ConcreteStrategyB.h"
#include "Strategy.h"
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
	Strategy * s1 = new ConcreteStrategyA();
	Context * cxt = new Context();
	cxt->setStrategy(s1);
	cxt->algorithm();

	Strategy *s2 = new ConcreteStrategyB();
	cxt->setStrategy(s2);
	cxt->algorithm();
	
	delete s1;
	delete s2;
	
	int rac1 = 0x1;
	int rac2 = 0x2;
	int rac3 = 0x4;
	int rac4 = 0x8;
	
	int i = 0xe;
	int j = 0x5;

	int r1 = i & rac1;
	int r2 = i & rac2;
	int r3 = i & rac3;
	int r4 = i & rac4;
	
	cout <<"res:" << r1 << "/" << r2 << "/" << r3 << "/" << r4 << endl;
	
	return 0;
}
```

```C++
///////////////////////////////////////////////////////////
//  Context.h
//  Implementation of the Class Context
//  Created on:      09-十月-2014 22:21:07
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_0DA87730_4DEE_4392_9BAF_4AC64A8A07A4__INCLUDED_)
#define EA_0DA87730_4DEE_4392_9BAF_4AC64A8A07A4__INCLUDED_

#include "Strategy.h"

class Context
{

public:
	Context();
	virtual ~Context();
	

	void algorithm();
	void setStrategy(Strategy* st);
	
private:
	Strategy *m_pStrategy;

};
#endif // !defined(EA_0DA87730_4DEE_4392_9BAF_4AC64A8A07A4__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  Context.cpp
//  Implementation of the Class Context
//  Created on:      09-十月-2014 22:21:07
//  Original author: colin
///////////////////////////////////////////////////////////

#include "Context.h"

Context::Context(){
}

Context::~Context(){
}

void Context::algorithm(){
	m_pStrategy->algorithm();
}

void Context::setStrategy(Strategy* st){
	m_pStrategy = st;
}
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteStrategyA.h
//  Implementation of the Class ConcreteStrategyA
//  Created on:      09-十月-2014 22:21:06
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_9B180F12_677B_4e9b_A243_1F5DAD93FE1D__INCLUDED_)
#define EA_9B180F12_677B_4e9b_A243_1F5DAD93FE1D__INCLUDED_

#include "Strategy.h"

class ConcreteStrategyA : public Strategy
{

public:
	ConcreteStrategyA();
	virtual ~ConcreteStrategyA();

	virtual void algorithm();

};
#endif // !defined(EA_9B180F12_677B_4e9b_A243_1F5DAD93FE1D__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteStrategyA.cpp
//  Implementation of the Class ConcreteStrategyA
//  Created on:      09-十月-2014 22:21:07
//  Original author: colin
///////////////////////////////////////////////////////////

#include "ConcreteStrategyA.h"
#include <iostream>
using namespace std;

ConcreteStrategyA::ConcreteStrategyA(){

}

ConcreteStrategyA::~ConcreteStrategyA(){

}

void ConcreteStrategyA::algorithm(){
	cout << "use algorithm A" << endl;
}
```

The strategy pattern is a design pattern that is easy to understand and use. The strategy pattern is the encapsulation of the algorithm, which separates the responsibility of the algorithm from the algorithm itself and delegates it to different object management.The policy pattern typically encapsulates a set of algorithms into a set of policy classes, which are subclasses of an abstract policy class.In a word, "take a set of algorithms and encapsulate each one so that they are interchangeable."

In the policy pattern, it is up to the client to decide which specific policy roles to use in which situations.

The strategy mode only encapsulates the algorithm, providing the convenience of inserting new algorithm into the existing system and "retiring" the old algorithm from the system. The strategy mode does not decide when to use which algorithm, but the choice of algorithm is determined by the client side.This improves the flexibility of the system to a certain extent, but the client needs to understand the differences between all specific policy classes in order to select the appropriate algorithm, which is also one of the disadvantages of the policy pattern, and to some extent increases the difficulty of using the client.

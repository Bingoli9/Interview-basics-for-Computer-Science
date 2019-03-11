## Bridge Pattern

Imagine that if we want to draw rectangle, circle, ellipse and square, we need at least four shape classes. However, if the drawn graph needs to have different colors, such as red, green and blue, there are at least two design schemes as follows:

The first is to provide a variety of colors for each shape.

The second design is to combine shapes and colors as needed

For a system with two dimensions of change (i.e. two causes of change), scheme 2 is adopted to design a system with fewer classes and more convenient system expansion.The second design is the application of bridge mode.Bridging patterns transform inheritance relationships into association relationships, thereby reducing class to class coupling and reducing the amount of code written.

![Bridge](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/Bridge.jpg?raw=true)

![seq_Bridge](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/seq_Bridge.jpg?raw=true)

```C++
#include <iostream>
#include "ConcreteImplementorA.h"
#include "ConcreteImplementorB.h"
#include "RefinedAbstraction.h"
#include "Abstraction.h"

using namespace std;

int main(int argc, char *argv[])
{
	
	Implementor * pImp = new ConcreteImplementorA();
	Abstraction * pa = new RefinedAbstraction(pImp);
	pa->operation();
	
	Abstraction * pb = new RefinedAbstraction(new ConcreteImplementorB());
	pb->operation();		
	
	delete pa;
	delete pb;
	
	return 0;
}

```

```C++
///////////////////////////////////////////////////////////
//  RefinedAbstraction.h
//  Implementation of the Class RefinedAbstraction
//  Created on:      03-十月-2014 18:12:43
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_4BA5BE7C_DED5_4236_8362_F2988921CFA7__INCLUDED_)
#define EA_4BA5BE7C_DED5_4236_8362_F2988921CFA7__INCLUDED_

#include "Abstraction.h"

class RefinedAbstraction : public Abstraction
{

public:
	RefinedAbstraction();
	RefinedAbstraction(Implementor* imp);
	virtual ~RefinedAbstraction();

	virtual void operation();

};
#endif // !defined(EA_4BA5BE7C_DED5_4236_8362_F2988921CFA7__INCLUDED_)

```

```C++
///////////////////////////////////////////////////////////
//  RefinedAbstraction.cpp
//  Implementation of the Class RefinedAbstraction
//  Created on:      03-十月-2014 18:12:43
//  Original author: colin
///////////////////////////////////////////////////////////

#include "RefinedAbstraction.h"
#include <iostream>
using namespace std;


RefinedAbstraction::RefinedAbstraction(){

}

RefinedAbstraction::RefinedAbstraction(Implementor* imp)
	:Abstraction(imp)
{
}

RefinedAbstraction::~RefinedAbstraction(){

}

void RefinedAbstraction::operation(){
	cout << "do something else ,and then " << endl;
	m_pImp->operationImp();
}

```


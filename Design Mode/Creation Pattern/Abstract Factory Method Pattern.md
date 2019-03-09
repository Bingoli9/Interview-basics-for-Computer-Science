## Abstract Factory Method Pattern

In the factory method model, specific factories are responsible for producing specific products, and each specific factory corresponds to a specific product. The factory method is also unique. Generally, there is only one factory method or a group of overloaded factory methods in a specific factory.But sometimes we need a factory that can provide multiple product objects instead of a single product object.

In order to understand the factory method pattern more clearly, two concepts need to be introduced first:

Product hierarchy: hierarchy the inheritance structure of products, such as an abstract class is a TV set, its subclasses are haier, hisense TV, TCL, TVS, abstract and specific brands, constitute a product hierarchy between abstraction is the parent of the television, and specific brand of TV set is its subclasses.

Product family: in the abstract factory pattern, product family is to point to by the same factory, located in different level of product structure in a set of products, such as haier electrical appliances factory production of TV sets, refrigerators, haier haier haier TV in the TV product hierarchy, haier refrigerators in the refrigerator in the hierarchy.

Abstract Factory Pattern: provides an interface for creating a set of related or interdependent objects without specifying their specific classes.The abstract factory pattern, also known as the Kit pattern, belongs to the object creation pattern.

![AbatractFactory](https://github.com/leekeiling/Design%20Mode/blob/master/pics/AbatractFactory.jpg?raw=true)

![seq_AbatractFactory](https://github.com/leekeiling/Design%20Mode/blob/master/pics/seq_AbatractFactory.jpg?raw=true)

```C++
#include <iostream>
#include "AbstractFactory.h"
#include "AbstractProductA.h"
#include "AbstractProductB.h"
#include "ConcreteFactory1.h"
#include "ConcreteFactory2.h"
using namespace std;

int main(int argc, char *argv[])
{
	AbstractFactory * fc = new ConcreteFactory1();
	AbstractProductA * pa =  fc->createProductA();
	AbstractProductB * pb = fc->createProductB();
	pa->use();
	pb->eat();
	
	AbstractFactory * fc2 = new ConcreteFactory2();
	AbstractProductA * pa2 =  fc2->createProductA();
	AbstractProductB * pb2 = fc2->createProductB();
	pa2->use();
	pb2->eat();
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteFactory1.cpp
//  Implementation of the Class ConcreteFactory1
//  Created on:      02-十月-2014 15:04:11
//  Original author: colin
///////////////////////////////////////////////////////////

#include "ConcreteFactory1.h"
#include "ProductA1.h"
#include "ProductB1.h"
AbstractProductA * ConcreteFactory1::createProductA(){
	return new ProductA1();
}


AbstractProductB * ConcreteFactory1::createProductB(){
	return new ProductB1();
}
```

```
///////////////////////////////////////////////////////////
//  ProductA1.cpp
//  Implementation of the Class ProductA1
//  Created on:      02-十月-2014 15:04:17
//  Original author: colin
///////////////////////////////////////////////////////////

#include "ProductA1.h"
#include <iostream>
using namespace std;
void ProductA1::use(){
	cout << "use Product A1" << endl;
}
```

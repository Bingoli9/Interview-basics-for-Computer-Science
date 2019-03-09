## Factory Method Pattern

The Factory Method Pattern, also known as the Virtual Constructor Pattern or the Polymorphic Factory Pattern, belongs to a class-creation Pattern.In factory method pattern, the parent factory is responsible for defining public interfaces, and the children factory is responsible for generating the specific products. The purpose is to delay product class instantiation operations ,in other words, the children factory is to instantiate a specific product class.

![FactoryMethod](https://github.com/leekeiling/Design%20Mode/blob/master/pics/FactoryMethod.jpg?raw=true)

![seq_FactoryMethod](https://github.com/leekeiling/Design%20Mode/blob/master/pics/seq_FactoryMethod.jpg?raw=true)

```C++
///////////////////////////////////////////////////////////
//  ConcreteFactory.cpp
//  Implementation of the Class ConcreteFactory
//  Created on:      02-十月-2014 10:18:58
//  Original author: colin
///////////////////////////////////////////////////////////

#include "ConcreteFactory.h"
#include "ConcreteProduct.h"

Product* ConcreteFactory::factoryMethod(){

	return  new ConcreteProduct();
}

```

```C++
#include "Factory.h"
#include "ConcreteFactory.h"
#include "Product.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	Factory * fc = new ConcreteFactory();
	Product * prod = fc->factoryMethod();
	prod->use();
	
	delete fc;
	delete prod;
	
	return 0;
}
```


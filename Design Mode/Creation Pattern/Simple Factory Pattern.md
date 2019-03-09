## Simple Factory Pattern

Consider a simple software application scenario, a software system can provide a number of different appearance button (such as radio buttons, rectangular button, diamond button, etc.), these buttons are derived from the same base class, but after the inherited base class different subclasses modify the part properties so that they can present different appearance, if we want to use these buttons, don't need to know the specific button in the name of the class, said just need to know the button class a parameter, and provides a call convenient method, into the parameter method can return a corresponding button, at this point, you can use a simple factory pattern.

Simple Factory Pattern: also known as the Static Factory Method Pattern, this is a class creation Pattern.In the simple factory pattern, different instances of the same class can be returned depending on the parameters.The simple factory pattern specifically defines a class to be responsible for creating instances of other classes, which often have a common parent class.

![SimpleFactory](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/SimpleFactory.jpg?raw=true)

![seq_SimpleFactory](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/seq_SimpleFactory.jpg?raw=true)

```C++
///////////////////////////////////////////////////////////
//  Factory.cpp
//  Implementation of the Class Factory
//  Created on:      01-十月-2014 18:41:33
//  Original author: colin
///////////////////////////////////////////////////////////

#include "Factory.h"
#include "ConcreteProductA.h"
#include "ConcreteProductB.h"
Product* Factory::createProduct(string proname){
	if ( "A" == proname )
	{
		return new ConcreteProductA();
	}
	else if("B" == proname)
	{
		return new ConcreteProductB();
	}
	return  NULL;
}
```

Separating the creation of objects from the business processing of the objects themselves can reduce the coupling of the system, making both relatively easy to modify.

The call to the factory class factory method, can be called directly by the name of the class, and you just need to pass in a simple parameters. In the actual development, the parameters will be saved in an XML format, such as the configuration file. Modifying parameters do not need to modify any source code.

The biggest problem with the simple factory model is that the responsibility of the factory class is relatively heavy. Adding new products requires modifying the judgment logic of the factory class, which is contrary to the principle of open and close.


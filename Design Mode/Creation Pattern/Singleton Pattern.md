## Singleton Pattern

Singleton Pattern: the Singleton Pattern ensures that a class has only one instance, and that it instantiates itself and provides that instance to the entire system. This class is called a Singleton class, and it provides methods for global access.

There are three main points of the singleton pattern: 

one is that a class can only have one instance;

The second is that it has to create the instance itself;

Third, it must provide this instance to the entire system itself.

The singleton pattern is an object creation pattern.

![seq_Singleton](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/Singleton.jpg?raw=true)



```C++
#include <iostream>
#include "Singleton.h"
using namespace std;

int main(int argc, char *argv[])
{
	Singleton * sg = Singleton::getInstance();
	sg->singletonOperation();
	
	return 0;
}
```

```C++
///////////////////////////////////////////////////////////
//  Singleton.cpp
//  Implementation of the Class Singleton
//  Created on:      02-十月-2014 17:24:46
//  Original author: colin
///////////////////////////////////////////////////////////

#include "Singleton.h"
#include <iostream>
using namespace std;

Singleton * Singleton::instance = NULL;
Singleton::Singleton(){

}

Singleton::~Singleton(){
	delete instance;
}

Singleton* Singleton::getInstance(){
	if (instance == NULL)
	{
		instance = new Singleton();
	}
	
	return  instance;
}


void Singleton::singletonOperation(){
	cout << "singletonOperation" << endl;
}
```


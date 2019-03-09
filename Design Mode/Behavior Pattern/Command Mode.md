## Command Mode

In software design, we often need to send a request to a certain object, but did not know who is the receiver requests, also don't know what is the requested operation, we need to specify the specific request to the receiver when the program is running, at this point, you can use the command mode to design, make request the sender to the receiver to eliminate the coupling between each other, and make the invocation of the relationship between objects more flexible.

Command mode can completely decouple the sender and the receiver, there is no direct reference relationship between the sender and the receiver, the object sending the request only needs to know how to send the request, not how to complete the request.This is the pattern motivation of command mode.

![Command](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/Command.jpg?raw=true)

![seq_Command](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/seq_Command.jpg?raw=true)

```C++
#include <iostream>
#include "ConcreteCommand.h"
#include "Invoker.h"
#include "Receiver.h"

using namespace std;

int main(int argc, char *argv[])
{
	Receiver * pReceiver = new Receiver();
	ConcreteCommand * pCommand = new ConcreteCommand(pReceiver);
	Invoker * pInvoker = new Invoker(pCommand);
	pInvoker->call();
	
	delete pReceiver;
	delete pCommand;
	delete pInvoker;
	return 0;
}
```

```C++
///////////////////////////////////////////////////////////
//  Receiver.h
//  Implementation of the Class Receiver
//  Created on:      07-十月-2014 17:44:02
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_8E5430BB_0904_4a7d_9A3B_7169586237C8__INCLUDED_)
#define EA_8E5430BB_0904_4a7d_9A3B_7169586237C8__INCLUDED_

class Receiver
{

public:
	Receiver();
	virtual ~Receiver();

	void action();

};
#endif // !defined(EA_8E5430BB_0904_4a7d_9A3B_7169586237C8__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  Receiver.cpp
//  Implementation of the Class Receiver
//  Created on:      07-十月-2014 17:44:02
//  Original author: colin
///////////////////////////////////////////////////////////

#include "Receiver.h"
#include <iostream>
using namespace std;

Receiver::Receiver(){

}

Receiver::~Receiver(){

}

void Receiver::action(){
	cout << "receiver action." << endl;
}
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteCommand.h
//  Implementation of the Class ConcreteCommand
//  Created on:      07-十月-2014 17:44:01
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_1AE70D53_4868_4e81_A1B8_1088DA355C23__INCLUDED_)
#define EA_1AE70D53_4868_4e81_A1B8_1088DA355C23__INCLUDED_

#include "Command.h"
#include "Receiver.h"

class ConcreteCommand : public Command
{

public:
	ConcreteCommand(Receiver * pReceiver);
	virtual ~ConcreteCommand();
	virtual void execute();
private:
	Receiver *m_pReceiver;



};
#endif // !defined(EA_1AE70D53_4868_4e81_A1B8_1088DA355C23__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  ConcreteCommand.cpp
//  Implementation of the Class ConcreteCommand
//  Created on:      07-十月-2014 17:44:02
//  Original author: colin
///////////////////////////////////////////////////////////

#include "ConcreteCommand.h"
#include <iostream>
using namespace std;


ConcreteCommand::ConcreteCommand(Receiver *pReceiver){
	m_pReceiver = pReceiver;
}



ConcreteCommand::~ConcreteCommand(){

}

void ConcreteCommand::execute(){
	cout << "ConcreteCommand::execute"  << endl;
	m_pReceiver->action();
}
```

```C++
///////////////////////////////////////////////////////////
//  Invoker.h
//  Implementation of the Class Invoker
//  Created on:      07-十月-2014 17:44:02
//  Original author: colin
///////////////////////////////////////////////////////////

#if !defined(EA_3DACB62A_0813_4d11_8A82_10BF1FB00D9A__INCLUDED_)
#define EA_3DACB62A_0813_4d11_8A82_10BF1FB00D9A__INCLUDED_

#include "Command.h"

class Invoker
{

public:
	Invoker(Command * pCommand);
	virtual ~Invoker();
	void call();

private:
	Command *m_pCommand;


};
#endif // !defined(EA_3DACB62A_0813_4d11_8A82_10BF1FB00D9A__INCLUDED_)
```

```C++
///////////////////////////////////////////////////////////
//  Invoker.cpp
//  Implementation of the Class Invoker
//  Created on:      07-十月-2014 17:44:02
//  Original author: colin
///////////////////////////////////////////////////////////

#include "Invoker.h"
#include <iostream>
using namespace std;

Invoker::Invoker(Command * pCommand){
	m_pCommand = pCommand;
}

Invoker::~Invoker(){

}

void Invoker::call(){
	cout << "invoker calling" << endl;
	m_pCommand->execute();
}
```

The essence of command mode is to encapsulate commands and separate the responsibility of issuing commands from the responsibility of executing commands

Each command is an operation: the requesting party makes a request for an operation to be performed;The receiving party receives the request and performs the operation.

Command mode allows the requesting party to be independent of the receiving party, making it unnecessary for the requesting party to know the interface of the receiving party, how the request was received, and whether, when and how the operation was performed.

The command pattern makes the request itself an object that can be stored and passed like any other object.

The key to the command pattern is the introduction of the abstract command interface, and the sender is programmed to the abstract command interface. Only concrete commands that implement the abstract command interface can be associated with the receiver.

### Advantage

Reduce the coupling of the system.

New commands can be added to the system easily.

You can easily design a command queue and macros (combined commands).

Undo and Redo for requests can be easily implemented.

### Disadvantage

Using command mode can cause some systems to have too many specific command classes.Because a specific command class needs to be designed for each command, some systems may require a large number of specific command classes, which affects the use of command patterns.



## V8 isolate/context/world/frame
### isolate
一个isolate是v8一份实例。在blink中isolate和线程是1:1关系。
### context
context是v8中全局变量范围概念。一个window对象对应一个context，不同frame具有不同的window对象。

### enter context and current context
一个isolate会在多个frame中执行js，每个frame中都有自己到context。  
要理解enter context and current    
context，需要了解两种运行时堆栈。  
第一个堆栈是js函数堆栈，该堆栈由v8管理。  
每个函数都有一个相关到context，我们将当前正在运行到函数的上下文称为current 
context；第二个堆栈以更粗糙的粒度运行。  
该堆栈由v8绑定故哪里，当v8绑定调用js时，v8绑定进入context并将context推送到堆栈。  
总之，entered context是从中开始当前js执行的context。  
current context是当前正在运行的js函数的context  

###  world
- main world
- isolate world
- worker world
main world用于执行网页的js脚本， isolate world用于执行扩展程序，  
主线程的isolate有一个main world和N个isolated world


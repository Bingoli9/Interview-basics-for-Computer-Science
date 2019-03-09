## RCU

RCU: Read Copy Update  
In RCU, Share Memory can be read without lock, but need to copy memory, update copy memory and  
use callback function to assign the pointer to point to new memory in right time.  


The difference of RCU and rwlock is RCU allow readers and writers to access share memory without block, but rwlock  
will block writer when there are readers accessing the share memory or block readers when there is writers accessing  
share memory.  

The pre-condition is that readers can not be blocked when access share memory.  

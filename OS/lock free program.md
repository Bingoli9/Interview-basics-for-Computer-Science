## Lock Free Program

#### Why Non-blocking sync?  
- Thread block because of competition, and delay response  
- dead lock
- live lock
- priority reverse
- performance reduction when use it unproperly


#### implementation level
- wait free
- lock-free
- obstruction-free


#### CAS atomic 
LL/SC atom read-modify-write   
Load-Link/Store-Condition(LL/SC) is used for lock free sync in CPU level  
LL[addr],dst: load data from addr in memory  
SC value,[addr]: update new value in current thread if last LL didn't change the value in memory  

CAS (Compare-And-Swap)
if LL/SC not offered, can use CAS atomic command to implement lock free program



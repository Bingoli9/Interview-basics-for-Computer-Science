## Chromium Preconenct

#### Connect Pool

Chrome maintains the connect pool for each protocol along.

Connect instance cannot be transfered from one pool to another, as a result, we need to decide which pool to allocate connect when request the network resource.



One Problem:

Preconnect does not consider private mode and all connect allocated from pool allows cookie connect, so the preconenct instance would not be used in the future and waste the resource.



#### Preconnect pool select rule

https://www.jianshu.com/p/1b26c3f04158


## Cache Line

Cache Line is minimum unit of transmission between CPU and memory. When a **cache line** is copied into **Cache** from memory, **cache** will build an entry for that **Cache Line**.

Since the Cache is much smaller than the main memory, there are situations where multiple main memory addresses can be mapped to the same Cache entry.

![cache-line-4](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/cache-line-4.png?raw=true)

#### Cache Coherence

In SMP systems, each CPU has its own local Cache.Therefore, the possibility of multiple copies of the same variable, or the same Line of Cache, in the local Cache of multiple processors creates a data consistency problem.

Assume that both processors A and B have a copy of the same variable in their respective local Cache lines and that the Cache Line is Shared. When processor A modifies the variable locally, it sets the Cache Line to the Modified state. What's more, before the processor B read the same variable, the processor A CPU core will notify the processor B's CPU core, and mark the correspond cache line as **Invalidate state**.

Later, if processor B reading and writing to the same variable and encounter a Cache Line with the state marked "Invalidate", it will result in a Cache Miss. As a result, the newest data will be copied into cache line from memory, and then the processor B would read and write the cache line correctly.

### False sharing

Cache Line false-sharing is caused by multiple threads on multiple cpus simultaneously modifying their variables.These variables appear to be different variables, but are actually stored in the same Cache Line.

In this situation, because of the **cache coherence**, it will cause Cache Miss, and significantly degrade performance.

![cache-line-false-sharing-5](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/cache-line-false-sharing-5.png?raw=true)




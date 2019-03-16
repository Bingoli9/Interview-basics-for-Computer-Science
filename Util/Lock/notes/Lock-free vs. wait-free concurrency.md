## Lock-free vs. wait-free concurrency

#### Lock-free

In lock-free systems, while any particular computation may be blocked for some period of time, all CPUs are able to continue performing other computations. To put it differently, while a given thread might be blocked by other threads in a lock-free system, all CPUs can continue doing other useful work without stalls.

#### Wait-free

Wait-free algorithms ensure that in addition to all CPUs continuing to do useful work, no computation can ever be blocked by another computation. Wait-free algorithms have stronger guarantees than lock-free algorithms, and ensure a high thorughput without sacrificing latency of a particular transaction.
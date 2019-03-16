## _mm_pause

PAUSE instructions increase the performance of the spin wait loop.When performing a cycle wait, the Intel P4 or Intel Xeon processors do perform a significant performance degradation upon exit due to the detection of a possible memory order violation.The PAUSE instruction is a reminder to the processor that the code sequence is a circular wait.Processors can take advantage of this tip to avoid memory order violations in most cases, which can greatly improve performance.For this reason, PAUSE instructions are recommended for use with circular waits.

The operation of this instruction is consistent in both 64-bit and non-64-bit modes.

example

```c++
   while (unlikely((v1 != v2)))
        _mm_pause();
```


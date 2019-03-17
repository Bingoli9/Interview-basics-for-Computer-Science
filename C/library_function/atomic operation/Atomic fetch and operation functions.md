## Atomic fetch and operation functions

This funtion performs an atmic operation on the variable \__v with the variable that \__p points to. The result is stored in the address that is specified by \__p.

A full memory barrier is created when this function is invoked.

```C++
__sync_fetch_and_and
__sync_fetch_and_nand
__sync_fetch_and_or
__sync_fetch_and_add
__sync_fetch_and_xor
__sync_fetch_and_sub
```

### Return value

The function returns the initial value of the variable that \__p points to.

## Atomic operation and fetch functions

```C++
__sync_and_and_fetch
__sync_nand_and_fetch
__sync_or_and_fetch
__sync__xor_and_fetch
__sync_add_and_fetch
__sync_sub_add_fetch
```

Those function proforms an atmic operation on the variable \__v with the variable that \__p points to. The result is stored in the address that is specified by \__p. 

A full memory barrier is created whrn this function is invoked.

## Return value

The function returns the new value of the variable that __p points to.

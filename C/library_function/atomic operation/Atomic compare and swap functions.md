## Atomic compare and swap functions

```C++
__sync_val_compare_and_swap
__sync_bool_compare_and_swap
```

This function compares the value of \__compVal to the value of the variable that \__p points to. If they are equal, the value of \__exchVal is stored in the address that is specified by __p; otherwise, no operation is performed.

A full memory barrier is created when this function is invoked.

### Prototype

```C++
T __sync_val_compare_and_swap (T* __p, U __compVal, V __exchVal, ...);
```

### Return value

The function returns the initial value of the variable that \__p points to.


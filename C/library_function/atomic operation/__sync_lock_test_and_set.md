## \__sync_lock_test_and_set

This function atomically assigns the value of __v to the variable that __p points to.

An acquire memory barrier is created when this function is invoked.

#### Prototype

```C++
T __sync_lock_test_and_set(T* __p, U __v, ...);
```

### Parameters

```C++
__p
The pointer of the variable that is to be set.
__v
The value to set to the variable that __p points to.
```

### Return value

The function returns the initial value of the variable that \__p points to.

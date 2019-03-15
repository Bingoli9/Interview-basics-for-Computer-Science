## \__sync_lock_release

### Purpose

This function releases the lock acquired by the \__sync_lock_test_and_set function, and assigns the value of zero to the variable that __p  points to.

A release memory barrier is created when this function is invoked.

### Prototype

```C++
void __sync_lock_release (T* __p, ...);
```

### Parameters

```C++
__p
The pointer of the variable that is to be set.
```


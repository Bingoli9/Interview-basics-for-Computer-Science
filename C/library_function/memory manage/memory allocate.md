## memory allocate

#### malloc()

```C++
void *malloc(size_t size)
```

Allocate enough memory to an object. 

#### calloc()

```C++
void *calloc(size_t nobj, size_t size);
```

Allocate memory to multiple object.

Allocate enough memory to construct an array composited with nobj elements of size **size**;

#### realloc

```C++
void *realloc(void *p, size_t size)
```

Change the size of the object that p points to to size bytes.




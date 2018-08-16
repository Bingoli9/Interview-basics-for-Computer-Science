## C语言动态内存分配

**1、函数原型**

1）malloc用来分配size字节的内存

```c++
void *malloc( 
   size_t size 
);
```

（2）calloc分配n个size大小的连续的空间

```c++
void *calloc( 
   size_t num,
   size_t size 
);
```

（3）realloc用于修改一个已经分配的内存块的大小

```c++
void *realloc( 
   void* memblock, 
   size_t size 
);
```

（4）_aligned_malloc:在一个特定的对齐边界分配内存(VS中)

```c++
void * _aligned_malloc(
    size_t size, 
    size_t alignment
);
```
## ZeroMemory

ZeroMemory is used to set a block of memory to zero in windows system.

```C++
#define RtlZeroMemory(Destination, Length) memset((Destination), 0, (Length))
#define ZeroMemory RtlZeroMemory
```

Notice:

memset and ZeroMemory can not be used to initialize class or structure that has STL, because it will also set STL object to zero and will cause a series of coruption problems.  




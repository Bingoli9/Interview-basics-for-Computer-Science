## Memory prefetch
对大数组非连续位置访问比较消耗CPU，原因是对于局部性很差的内存访问逻辑，对cache是不友好的。
x86 cpu提供了prefetch系列指令，用于将指定地址的内存预取到cache中。prefetch ($rax)将以$rax锁保存的值为地址的内存所在的cache line载入每一级cache。在适当位置加入preftch之后，程序相应的cpu热点可以消除，提升程序性能。

```C++
int run_withprefetch(const int *array, int size, int step, int prefetch)
{
    int result = 0;
    printf("run with prefetch(%d)...\n", prefetch);
    for (int i = 0; i < step; i++) {
        for (int j = i; j < size; j += step) {
            int k = j + step * prefetch;
            if (k  < size) {
                _mm_prefetch(&array[k], _MM_HINT_T0);
            }
            result += calcu(array[j]);
        }
    }
    return result;
}
```

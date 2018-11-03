## mmap
C++/C 内存分配和管理方式的一种。
mmap 和 munmap是Unix底层一种内存管理方式，优点是内存分配速度快，缺点是需要程序员完全由自己来维护分配的虚拟内存，没有任何其他辅助的数据结构来帮助维护内存空间。
**用于文件映射**

在有时候，项目的数据量特别大，而且源源不断的到来，这个时候，利用传统的IO文件流写文件势必效率很低跟不上节奏

```C++
int main(int argc, const char * argv[]) {
    //申请内存
    int* arr = static_cast<int>(mmap(
    	NULL,  //分配的首地址
    	getpagesize(),	// 分配的内存大小（必须是页的整数倍，32为1页=4k）
    	PORT_READ | PORT_WRITE, //映射区保护权限：读\写
    	MAP_ANON | MAP_SHARED, //匿名映射（不涉及文件io），后面连个参数忽略
    	0, //要映射到内存的文件描述符
    	0, //文件映射的偏移量，通常设置为0，必须是页的整数倍
    ))
    *arr = 10;
    *(arr + 1) = 20;
    *(arr + 2) = 30;
    
    //释放指针arr指向的内存区域，并制定释放的内存大小
    munmap(arr, getpagesize());
}
```
## ValGrind
包含Memcheck、Cachegrind、Helgrind、Callgrind和Massif

### Memcheck
检测程序中出现的内存问题，所有对内存的读写都会检测到，一切对malloc()/free()/new/delete的调用都会被捕获。

### Callgrind
建立函数调用图

### Cachegrind
Cache分析器，它模拟CPU中的一级缓存l1, Dl和二级缓存，能够精确地指出程序中cache的丢失和命中。如果需要可以提供cache的丢失次数，内存引用次数以及每行代码。每个函数，每个模块和整个程序产生的指令数。

### Helgrind
检验多线程中出现问题

### Massif
堆栈分析器，它能测量程序在堆栈中使用了多少内存，告诉我们堆块，堆管理和栈的大小。Massif能帮助我梦减少内存的使用，在带有虚拟内存的现代系统中，它能够加速我们程序的运行，减少程序停留在交换区中的几率。

###注意
 1. Valgrind不检查静态分配数组的使用情况
 2. Valgrind占用了更多内存-可达两倍与你程序的正常使用量。


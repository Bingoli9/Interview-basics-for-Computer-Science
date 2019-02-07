## memory defence
asm volatile("" ::: "memory")  

or even  

__asm__ __volatile__("" ::: "memory")


2）__asm__用于指示编译器在此插入汇编语句  
3）__volatile__用于告诉编译器，严禁将此处的汇编语句与其它的语句重组合优化。即：原原本本按原来的样子处理这这里的汇编。  
4） memory 强制 gcc 编译器假设 RAM 所有内存单元均被汇编指令修改，这样 cpu 中的 registers 和 cache 中已缓存的内存单元中的数据将作废。  
cpu 将不得不在需要的时候重新读取内存中的数据。这就阻止了 cpu 又将 registers, cache 中的数据用于去优化指令，而避免去访问内存。  

## free

1. free只是释放了malloc申请的内存，并不改变指针的值。free的是vert_x所指向地址的内存。free只是释放了指针所指向的  
地址空间，本质上做了一些标记而已，所以指针及空间内容都还是存在的，只不过有隐患。

2. free(vert_x)释放了vert_x指示的内存空间，vert_x这个指针变量本身仍然存在。是悬垂指针问题。

3. 由于指针所指向的内存已经释放，如果不指向NULL的话，将指针指向NULL

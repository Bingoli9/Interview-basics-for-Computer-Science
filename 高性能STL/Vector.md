## Vector

#### 提前分配足够空间以避免不必要的重新分配和复制周期。

#### 使用shrink_to_fit()释放vector占用的内存。 
 clear 和 erase不会释放内存空间
#### 在填充或者拷贝vector是后，使用赋值而不是insert 或者 push_back()

#### 遍历vector尽量用迭代器

#### 尽量避免在vector前部插入元素
 
#### 插入元素使用emplace_back() 而不是 push_back()
理论上，“安置”更有效率。


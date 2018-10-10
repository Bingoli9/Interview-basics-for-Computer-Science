#### 迭代器erase注意事项

iterator erase(   iterator _Where);
iterator erase(   iterator _First,   iterator _Last);
如果是删除指定位置的元素时：
返回值是一个迭代器，指向删除元素下一个元素;

如果是删除某范围内的元素时：返回值也表示一个迭代器，指向最后一个删除元素的下一个元素;

#### map的存储结构

高度平衡的红黑树

#### vector的底层（存储）机制

vector就是一个动态数组，里面有一个指针指向一片连续的内存空间，当空间不够装下数据时，会自动申请另一片更大的空间（一般是增加当前容量的50%或100%），然后把原来的数据拷贝过去，接着释放原来的那片空间；当释放或者删除里面的数据时，其存储空间不释放，仅仅是清空了里面的数据。

#### std::vector的自增长机制

当已经分配的空间不够装下数据时，分配双倍于当前容量的存储区，把当前的值拷贝到新分配的内存中，并释放原来的内存。

#### list自带排序函数的排序原理

将前两个元素合并，再将后两个元素合并，然后合并这两个子序列成4个元素的子序列，重复这一过程，得到8个，16个，...，子序列，最后得到的就是排序后的序列。

```c++
void List::sort()
{
	List carry;
	List counter[64];  //数组元素为链表
	int fill = 0;
	while (head->next != tail)
	{
		carry.transfer(carry.getHead()->next, head->next, head->next->next); //head是哨兵，不存放有效值
		                                                                     //head->next元素被移走，所以while循环不需要head=head->next;
		int i = 0;
		while (i < fill && counter[i].getHead()->next != counter[i].getHead())//counter[i]不是空
		{
			counter[i].merge(carry);
			carry.swap(counter[i++]);
		}
		carry.swap(counter[i]);
		if (i == fill) ++fill;
	}
	for (int i = 1; i < fill; i++)
		counter[i].merge(counter[i - 1]);   //通过这个实现排序（将有序的链表合成一个新的有序链表）
	swap(counter[fill - 1]);
}
```

#### deque的底层机制

deque动态地以分段连续空间组合而成，随时可以增加一段新的连续空间并链接起来。不提供空间保留功能。

注意：除非必要，我们尽可能选择使用vector而非deque，因为deque的迭代器比vector迭代器复杂很多。对deque排序，为了提高效率，可先将deque复制到一个vector上排序，然后再复制回deque。

deque采用一块map（不是STL的map容器）作为主控，其为一小块连续空间，其中每个元素都是指针，指向另一段较大的连续空间（缓冲区）。

deque的迭代器包含4个内容：

1）cur：迭代器当前所指元素

2）first：此迭代器所指的缓冲区的头。

3）last：缓冲区尾。

4）node：指向管控中心。

#### deque与vector的区别

1）vector是单向开口的连续线性空间，deque是双向开口的连续线性空间。（双向开口是指可以在头尾两端分别做元素的插入和删除操作）。

2）deque没有提供空间保留功能，而vector则要提供空间保留功能。

3）deque也提供随机访问迭代器，但是其迭代器比vector迭代器复杂很多。

map底层机制









#### map底层机制

map以RB-TREE为底层机制。RB-TREE是一种平衡二叉搜索树，自动排序效果不错。

通过map的迭代器不能修改其键值，只能修改其实值。所以map的迭代器既不是const也不是mutable。

#### vector插入删除和list有什么区别

vector插入和删除数据，需要对现有数据进行复制移动，如果vector存储的对象很大或者构造函数很复杂，则开销较大，如果是简单的小数据，效率优于list。

list插入和删除数据，需要对现有数据进行遍历，但在首部插入数据，效率很高。

#### hashtable，hash_set，hash_map的区别

#### hash_map与map的区别？什么时候用hash_map，什么时候用map？

构造函数：hash_map需要hash function和等于函数，而map需要比较函数（大于或小于）。

存储结构：hash_map以hashtable为底层，而map以RB-TREE为底层。 

总的说来，hash_map查找速度比map快，而且查找速度基本和数据量大小无关，属于常数级别。而map的查找速度是logn级别。但不一定常数就比log小，而且hash_map还有hash function耗时。

如果考虑效率，特别当元素达到一定数量级时，用hash_map。

考虑内存，或者元素数量较少时，用map。

#### map和set的3个问题

1. 为何map和set的插入删除效率比其他序列容器高。

   因为不需要内存拷贝和内存移动

2. 为何map和set每次Insert之后，以前保存的iterator不会失效？

   因为插入操作只是结点指针换来换去，结点内存没有改变。而iterator就像指向结点的指针，内存没变，指向内存的指针也不会变。

3. 当数据元素增多时（从10000到20000），map的set的查找速度会怎样变化？

   RB-TREE用二分查找法，时间复杂度为logn，所以从10000增到20000时，查找次数从log10000=14次到log20000=15次，多了1次而已。

#### vector中begin和end函数返回的是什么？

begin返回的是第一个元素的迭代器，end返回的是最后一个元素后面位置的迭代器。

#### 为什么vector的插入操作可能会导致迭代器失效？

vector动态增加大小时，并不是在原空间后增加新的空间，而是以原大小的两倍在另外配置一片较大的新空间，然后将内容拷贝过来，并释放原来的空间。由于操作改变了空间，所以迭代器失效。

#### vector、list、map、deque用erase（it）后，迭代器的变化。

vector和deque是序列式容器，其内存分别是连续空间和分段连续空间，删除迭代器it后，其后面的迭代器都失效了，此时it及其后面的迭代器会自动加1，使it指向被删除元素的下一个元素。

list删除迭代器it时，其后面的迭代器都不会失效，将前面和后面连接起来即可。

map也是只能使当前删除的迭代器失效，其后面的迭代器依然有效。

#### hashtable和hashmap的区别

hashmap以hashtable为底层。主要有以下几点不同：
1）hashtable是Dictionary的子类，而hashmap是Map接口的一个实现类。

2）hashtable中的方法是同步的，而hashmap的方法不同步。




## Small Map
开始使用数组实现，当超过其指定大小时切换到其他容器类型  

std::map 使用的时候每个元素都需要内存分配，且使用红黑树作为底层结构，将产生很多代码  

但对于存储少量元素，采用vector暴力搜索通常效率不会太低，抵消内存分配的影响  

base::map，查找复杂度为O(1), 但内部的哈希表将会产生更多的空间资源，并且容易写出看似正确的代码  

```C++
SmallMap<hash_map<int, int> > m;
m[0] = 5;
m[9] = 2;

SmallMap<hash_map<int, int> >::iterator iter(m.begin());
const SmallMap<hash_map<int, int> >& ref = m;
bool res = ref.find(1234) != m.end();


SmallMap<hash_map<std::string, int> > ms;
ms["monday"] = 1;
ms["tuesday"] = 2;
ms["wednesday"] = 3;

SmallMap<std::map<int, int>, 4, std::equal_to<int> > mmap;
mmap[9] = 2;
mmap[0] = 5;

SmallMap<std::map<int, int>, 4, std::equal_to<int> >::iterator iter(
      mmap.begin());
```



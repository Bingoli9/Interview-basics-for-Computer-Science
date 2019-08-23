## MRU Cache

最近最少使用缓冲区模板，允许通过一个键值在常数事件内访问一个元素项，并且容易识别将要删除的最近最少使用元素项  

MRUCacheStandardMap: 内部声明的标准std::map类型的模板  

MRUCacheBase：最近最少使用MRU缓存基类  

template \<class KeyType, class PayloadType, class DeletorType, tmplate \<typename, typename> class MapType = MRUCacheStandardMap> class MRUCacheBase;  

#### 成员函数

- 不支持拷贝复制和复制分配操作
- 提供显式参数为列表最大数据容器长度的构造函数
- 提供max_size：返回最大列表容器长度
- 提供Get操作：获取指定的Key内容，若获取失败则返回end();成功则调整内部列表将找到的key移动到列表表首并返回该key的内容迭代器；调整列表使用slice方法，可以会有效率问题。
- 提供erase操作
- ShrinkToSize
- Clear：清空cache操作
- 提供begin，end，rbegin，rend迭代器操作

#### MRUCacheNullDeletor

#### MRUCache
作为一般操作容器；内部提供显式构造函数，参数max_size指定列表数据容器长度；此外不允许赋值构造和拷贝构造  

#### MRUCachePointerDeletor
作为OwningMRUCache的销毁器，删除荷载指针对象  

#### OwningMRUCache
主要是容乃非常量指针类型的荷载对象，以允许被移除、替代、销毁时刻被删除  

#### HashingMRUCache
最后一个模板参数为base::hash_map作为基础映射容器  

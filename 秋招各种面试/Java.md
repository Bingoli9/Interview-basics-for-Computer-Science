#### iterator使用注意事项

Java中的Iterator功能比较简单，并且只能单向移动：

1.  使用方法iterator()要求容器返回一个Iterator。第一次调用Iterator的next()方法时，它返回序列的第一个元素。注意：**iterator()方法是java.lang.Iterable接口,被Collection继承**。
2. **想要使用Iterator， 要求这个class implement Interface Iterable<T>**
3. 使用next()获得序列中的下一个元素。
4. 使用hasNext()检查序列中是否还有元素。
5.  使用remove()将迭代器新返回的元素删除。
6. Iterator是Java迭代器最简单的实现，为List设计的ListIterator具有更多的功能，它可以从两个方向遍历List，也可以从List中插入和删除元素。

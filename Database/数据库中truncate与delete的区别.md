## 数据库中truncate与delete的区别

而DELETE和TRUNCATE TABLE都是删除表中的数据的语句，它们的不同之处在于：

1、TRUNCATE TABLE比DELETE的速度快；

2、TRUNCATE TABLE 是删除表的所有行，而DELETE是删除表的一行或者多行（除非DELETE不带WHERE语句）；

3、在删除时如果遇到任何一行违反约束（主要是外键约束），TRUNCATE TABLE仍然删除，只是表的结构及其列、约束、索引等保持不变，但DELETE是直接返回错误；

4、对于被外键约束的表，不能使用TRUNCATE TABLE，而应该使用不带WHERE语句的DELETE语句。

5、如果想保留标识计数值，要用DELETE，因为TRUNCATE TABLE会对新行标志符列搜用的计数值重置为该列的种子。

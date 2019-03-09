## Oracle表存在外键约束，无法truncate table，但delete table可以



## 问题原因

虽然truncate table在删除数据的速度上会占有一定的优势，但并不是在所有的情况我们都可以使用truncate，存在以下情况就使用truncate就会失败。 
1，要删除数据的表包含foreign key约束（被其他表引用），而delete则可以通过级联删除来删除相关联的数据。 
2，被索引视图引用过的表，也不能使用truncate。

## 解决方案

有外键的表只能用delete，不能用truncate，这是语法规定，要么就取消外键再truncate。 
可以先禁用外键约束，删除完毕后，再启动外键约束。

#### 查找外键关联

```
SELECT T1.TABLE_NAME,
       T2.TABLE_NAME AS "TABLE_NAME(R)",
       T1.CONSTRAINT_NAME,
       T1.R_CONSTRAINT_NAME AS "CONSTRAINT_NAME(R)",
       A1.COLUMN_NAME,
       A2.COLUMN_NAME AS "COLUMN_NAME(R)"
  FROM USER_CONSTRAINTS T1
 INNER JOIN USER_CONSTRAINTS T2 ON T1.R_CONSTRAINT_NAME =
                                   T2.CONSTRAINT_NAME
 INNER JOIN USER_CONS_COLUMNS A1 ON T1.CONSTRAINT_NAME = 
                                    A1.CONSTRAINT_NAME
 INNER JOIN USER_CONS_COLUMNS A2 ON T1.R_CONSTRAINT_NAME =
                                    A2.CONSTRAINT_NAME
 WHERE T2.TABLE_NAME = '要删的表名';1234567891011121314
```

#### 外键禁用/开启

```
--禁用约束：
alter table XXX disable constraint XXX;
--启用约束
alter table XXX enable constraint XXX;1234
```

#### 实例

![这里写图片描述](https://img-blog.csdn.net/20180307171625978?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveW91bmd4dg==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

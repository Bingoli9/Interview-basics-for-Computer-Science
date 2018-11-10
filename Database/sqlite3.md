## sqlite3

### env
sqlite3.lib  sqlite3.dll  
### 打开或者创建数据库

```c++
sqlite3 *sql = NULL; // 一个打开的数据库实例
    const char * path = "..../test.db";//某个sql文件的路径

    // 根据文件路径打开数据库连接。如果数据库不存在，则创建。
    // 数据库文件的路径必须以C字符串传入。
    int result = sqlite3_open_v2(path, &sql, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_NOMUTEX | SQLITE_OPEN_SHAREDCACHE, NULL);

    if (result == SQLITE_OK) {
        std::clog << "打开数据库连接成功";
    }
    else {
        std::clog << "打开数据库连接失败";
    }
```

### 执行不返回数据的SQL语句 
```C++
	const char *sqlSentence = "INSERT INTO t_person(name, age) VALUES('夏明', 22); ";        //SQL语句
    sqlite3_stmt *stmt = NULL;        //stmt语句句柄
    //进行插入前的准备工作——检查语句合法性
    //-1代表系统会自动计算SQL语句的长度
    int result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);

    if (result == SQLITE_OK) {
        std::clog<< "添加数据语句OK";
        //执行该语句
        sqlite3_step(stmt);
    }
    else {
        std::clog << "添加数据语句有问题";
    }
    //清理语句句柄，准备执行下一个语句
    sqlite3_finalize(stmt);
```

### 查询语句
```C++
const char *sqlSentence = "SELECT name, age FROM t_person WHERE age < 30;";    //SQL语句
    sqlite3_stmt *stmt = NULL;    // stmt语句句柄

    //进行查询前的准备工作——检查语句合法性
    //-1代表系统会自动计算SQL语句的长度
    int result = sqlite3_prepare_v2(sql, sqlSentence, -1, &stmt, NULL);

    if (result == SQLITE_OK) {
        std::clog <<  "查询语句OK";
            // 每调一次sqlite3_step()函数，stmt语句句柄就会指向下一条记录
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                // 取出第0列字段的值
                const unsigned char *name = sqlite3_column_text(stmt, 0);
                // 取出第1列字段的值
                int age = sqlite3_column_int(stmt, 1);
                //输出相关查询的数据
                std::clog << "name = " << name <<", age = "<< age;
            }
    }
    else {
        std::clog << "查询语句有问题";
    }
    //清理语句句柄，准备执行下一个语句
    sqlite3_finalize(stmt);
```

### 关闭数据库
```C++
	if(sql) {
		sqlite3_close_v2(sql);
		sql = nullptr;
```



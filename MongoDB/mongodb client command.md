## mongodb client command

### start mongodb

```C++
mongod --dbpath
```

### show database

```C++
show dbs
```

### show current database

```C++
db
```

### select specific database to operate

```C++
use $databaseName
```

### create database

```C++
use $databaseName
```

### login database

```C++
db.auth(username, passwd)
```

### show tables 

```C++
db.getCollectionNames()
```

### query operation

```C++
db.CollectionName.find({}).pretty()
```

### query Condition

```C++
$gt
$lt
$lte
$elemMatch
```

### remove data

```C++
db.CollectionName.remove({})
```

### remove table

```C++
db.Collection.drop()
```

### insert data

```C++
db.CollectionName.insert({})
```

### update data

```C++
db.CollectionName.updata({},{})
```




## streambuf

使用streambuf加速读入输出  
一般情况下，在C++中，iostream内的cin和cout是比scanf和printf慢的，  
这主要是为了同时兼容iostream和stdio，iostream与stdio的缓冲区被绑到一起  

为了提高cin和cout的效率，我们可以取消iostream与stdio的同步，以及cin和cout的stream的绑定：  
```C++
std::ios::sync_with_stdio(false)
cin.tie(NULL)
cout.tie(NULL)
```



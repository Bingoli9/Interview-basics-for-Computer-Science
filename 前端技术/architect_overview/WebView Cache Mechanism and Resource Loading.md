## WebView Cache Mechanism and Resource Loading 

#### Android WebView Efficiency Problem

- Slow Android WebView H5 page loading

- 耗费流量 

  

#### The reason of slow H5 page loading

<center>
  <img src = "https://upload-images.jianshu.io/upload_images/944365-def9d2485233ff9f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700"/>
</center>

### Cache Mechanism 

The field Cache-Control(Expires) and Last-Modified(or Etag), etc can be used to control file cache

#### Cache-Control

If the service response package includes Cache-Control:max-age=600, means that files should be cached in local for 600 secs. In next 600 secs, if request this resource, the browser will not send HTTP request but use local cache file instead.

#### Expires

It's similar to Cache-Control

#### Last-Modified

Mark the latest update time  of files in service side

#### Etag

It's similar to Last-Modified



### Application Cache Mechanism

- The element need to be cached is file, and the files have update mechanism 
- AppCache mechanism has two key point: manifest attribute and manifest file

```C++
<!DOCTYPE html>
<html manifest="demo_html.appcache">
// HTML 在头中通过 manifest 属性引用 manifest 文件
// manifest 文件：就是上面以 appcache 结尾的文件，是一个普通文件文件，列出了需要缓存的文件
// 浏览器在首次加载 HTML 文件时，会解析 manifest 属性，并读取 manifest 文件，获取 Section：CACHE MANIFEST 下要缓存的文件列表，再对文件缓存
<body>
...
</body>
</html>
 
// 原理说明如下：
// AppCache 在首次加载生成后，也有更新机制。被缓存的文件如果要更新，需要更新 manifest 文件
// 因为浏览器在下次加载时，除了会默认使用缓存外，还会在后台检查 manifest 文件有没有修改（byte by byte)
发现有修改，就会重新获取 manifest 文件，对 Section：CACHE MANIFEST 下文件列表检查更新
// manifest 文件与缓存文件的检查更新也遵守浏览器缓存机制
// 如用户手动清了 AppCache 缓存，下次加载时，浏览器会重新生成缓存，也可算是一种缓存的更新
// AppCache 的缓存文件，与浏览器的缓存文件分开存储的，因为 AppCache 在本地有 5MB（分 HOST）的空间限制

```



### Dom Storage Cache Mechanism

DOM Storage includes sessionStorage and localStorage. Both have the same usage, but their difference is:

- sessionStorage: temporary storage. It will lose after close the page
- localStorage: persistency storage. The data will not lose after close the page

Dom Storage wil store temporary and simple data

```C++
    // 通过设置 `WebView`的`Settings`类实现
        WebSettings settings = getSettings();
 
        settings.setDomStorageEnabled(true);
        // 开启DOM storage
```



#### Web SQL Database Cache Mechanism

Based on SQL database

```C++
// 通过设置WebView的settings实现
        WebSettings settings = getSettings();
 
        String cacheDirPath = context.getFilesDir().getAbsolutePath()+"cache/";
        settings.setDatabasePath(cacheDirPath);
        // 设置缓存路径
 
        settings.setDatabaseEnabled(true);
        // 开启 数据库存储机制
```

### IndexedDB Cache Mechanism

Based on NoSQL DataBase

<center>
  <img src = "https://upload-images.jianshu.io/upload_images/944365-0237085ddd823faa.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700"/>
</center>

### File System

Virtual file system for H5 webpage data

Offerring temporary and persistency cache storage

- Can store big binary data
- can pre-load resource file
- can directly edit the file



<center>
  <img src = "https://upload-images.jianshu.io/upload_images/944365-3d023c81c7b43053.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700"/>
</center>

### Cache Mode

```C++
// 缓存模式说明: 
      // LOAD_CACHE_ONLY: 不使用网络，只读取本地缓存数据
      // LOAD_NO_CACHE: 不使用缓存，只从网络获取数据.
      // LOAD_DEFAULT: （默认）根据cache-control决定是否从网络上取数据。
      // LOAD_CACHE_ELSE_NETWORK，只要本地有，无论是否过期，或者no-cache，都使用缓存中的数据。

```





### Self-designed cache

<center>
  <img src = "https://upload-images.jianshu.io/upload_images/944365-9153060a7444aa42.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700"/>
</center>

1. 事先将更新频率较低、常用 & 固定的`H5`静态资源 文件（如`JS`、`CSS`文件、图片等） 放到本地
2. 拦截`H5`页面的资源网络请求 并进行检测
3. 如果检测到本地具有相同的静态资源 就 直接从本地读取进行替换 而 不发送该资源的网络请求 到 服务器获取

<center>
  <img src = "https://upload-images.jianshu.io/upload_images/944365-5474af4c8a530c07.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/700"/>
</center>
















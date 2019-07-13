## Disk Cache
android 用到的磁盘缓存大多基于DiskLruCache实现的
```C++
DiskLruCache mDiskLruCache = null;
try {
	File cacheDir = getDiskCacheDir(context, "thumbnails");
	if (!cacheDir.exists()) {
		cacheDir.mkdirs();
	}
	mDiskLruCache = DiskLruCache.open(cacheDir, getAppVersion(context), 1, 10 * 1024 * 1024);
} catch (IOException e) {
	e.printStackTrace();
}
```

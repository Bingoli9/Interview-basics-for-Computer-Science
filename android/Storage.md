## Storage
Android设备包括两类存储区域： Internal Storage和External Storage  

Internal Storage：  
    - 总是可用
    - 这里的文件只能由app访问
    - Iternal是我们在想确保不被用户与其他app所访问的最佳存储区域。

External Storage:  
    - 并不总是可用的，因为用户有时会通过USB存储模式挂载外部存储器，当取下挂载的这部分后，就无法对其进行访问了。
    - 是大家都可以访问的，因此保存在这里的文件可能被其他程序访问。
    - 当用户卸载我们的app时，系统仅仅会删除external根目录（getExternalFilesDir()）下的相关文件。
    - External是在不需要严格的访问权限并且希望这些文件能够被其他app所共享或者是允许用户通过电脑访问时的最佳存储区域。


### 保存到Internal Storage
    - getFilesDir() : 返回一个File，代表了我们app的internal目录。
    - getCacheDir() : 返回一个File，代表了我们app的internal缓存目录。


### 保存文件到External Storage
    - public app卸载后数据不删除, 比如album目录
    - private app私有，卸载后数据删除

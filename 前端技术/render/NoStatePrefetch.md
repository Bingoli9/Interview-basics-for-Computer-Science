# NoStatePrefetch

#### 简介

在NoStatePrefetch之前有Prerender预渲染特性，Prerender是预创建隐藏tab来加载网页，而NoStatePrefetch则是控制Prerender预渲染仅仅拉去主文档和子资源，不解析排版网页。NoStatePrefetch目的是减少Prerender的性能消耗的影响。

#### NoStatePrefetch Motivation

##### 减少内存消耗

Prerender每个页面的内存压力大概是150M，而NoStatePrefetch，内存压力大概为50M

##### 避免网页异常行为

With prerendering, no user-facing (e.g., playing music or video) or stateful actions (e.g., mutating session or local storage) should occur. 

#### Implementation

1. Prerender触发之后，webview根据内存压力选择Prerender还是NoStatePrefetch

2. 用Dedicated Render来加载Preender网页

3. HTMLPreScanner预扫描主文档，加载网页内所有资源

4. 子资源网络请求优先级为IDLE

5. 资源请求下来之后缓存

   






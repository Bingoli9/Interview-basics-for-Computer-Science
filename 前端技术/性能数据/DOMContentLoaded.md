## DOMContentLoaded

HTML网页包括三类事件：

- DOMContnetLoaded。浏览器已经加载HTML，DOM Tree已经创建，但是图片资源和样式表还没有加载

- load。浏览器加载完所有资源

- beforeunload/unload 用户离开网页

  - beforeunload 用户即将离开页面，可以通知用户是否需要保存修改或者是否真的离开网页
  - unload 用户几乎离开页面，但javascript可以初始化一些操作，例如发送数据

  
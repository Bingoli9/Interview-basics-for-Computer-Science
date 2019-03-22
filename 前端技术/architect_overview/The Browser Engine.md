Browser FrameWork

![673016243-5c739ed62d7a5_articlex](https://github.com/leekeiling/Interview-basics-for-Computer-Science/blob/master/pics/673016243-5c739ed62d7a5_articlex.png?raw=true)

#### The User Interface     

Provides a way for users to interact with Browser Engine. These include the address bar, the forward/back button, the bookmarks menu, and so on. 

### The Browser Engine

Transfering instructions between UI and the rendering engine. Providing high level interfaces of The Rendering Engine. On the one hand, it provides methods to initialize the url and other high level browser action, on the other hand, Thr Browser Engine offers message about error, loading process and so on.

### The Rendering Engine

为给定的URL提供可视化的展示。它解析JavaScript、Html、Xml，并且User Interface中展示的layout。其中关键的组件是Html解析器，它可以让Rendering Engine展示差乱的Html页面。 值得注意：不同的浏览器使用不同的Rendering Engine。例如IE使用Trident，Firefox使用Gecko，Safai使用Webkit。Chrome和Opera使用Webkit（以前是Blink）

#### The Networking

基于互联网HTTP和FTP协议，处理网络请求。网络模块负责Internet communication and security，character set translations and MIME type resolution。另外网络模块还提供获得到文档的缓存，以减少网络传输。为所有平台提供底层网络实现，其提供的接口与平台无关

#### The JavaScript Interpreter

解释和运行网站上的js代码，得到的结果传输到Rendering Engine来展示。

#### The UI Backend

用于绘制基本的窗口小部件，比如组合框和窗口。而在底层使用操作系统的用户界面方法，并公开与平台无关的接口。

#### The Data Storage

管理用户数据，例如书签、cookie和偏好设置等。



                                                                                                           

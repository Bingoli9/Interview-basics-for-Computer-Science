## HTTP2

#### HTTP/1.1 Problems

- TCP connected number limit

  对于同一个域名，浏览器最多只能同时创建 6~8 个 TCP 连接 (不同浏览器不一样)。为了解决数量限制，出现了 `域名分片` 技术，其实就是资源分域，将资源放在不同域名下 (比如二级子域名下)，这样就可以针对不同域名创建连接并请求，以一种讨巧的方式突破限制，但是滥用此技术也会造成很多问题，比如每个 TCP 连接本身需要经过 DNS 查询、三步握手、慢启动等，还占用额外的 CPU 和内存，对于服务器来说过多连接也容易造成网络拥挤、交通阻塞等

- Head of Line Blocking

  每个TCP连接仅仅能处理一个请求-响应，浏览器按FIFO原则处理请求。

  pipeline技术解决上述问题，但仍然会出现请求等待情况。

- Header内容多，每次请求Header不会变化太多，没有相应的压缩传输优化方法

- 为了尽可能减少请求数，合并文件，但造成单个请求内容变大眼吃变高，且内嵌的资源不能有效地使用缓存机制

- 明文传输不安全

#### HTTP2优势

- 二进制分帧层（Binary Framing Layer）

- 多路复用（MultiPlexing）

  在一个TCP连接上，想对方不断发送帧，每帧的stream identifier标明帧数属于哪个流，然乎在对方接收时，根据stream identifier拼接每个流的所有帧组成一整块数据。

  所以http2对于同一域名只需要创建一个连接，而不是http/1.1创建6-8个连接

  <center>
    <img src = "https://upload-images.jianshu.io/upload_images/5578817-4aafa5f3dc589fd3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/981/format/webp"/>
  </center>

- 服务端推送（Server Push）

- Header压缩（HPACK）

- 应用层的重置连接

  对于 HTTP/1 来说，是通过设置 tcp segment 里的 reset flag 来通知对端关闭连接的。这种方式会直接断开连接，下次再发请求就必须重新建立连接。HTTP/2 引入 RST_STREAM 类型的 frame，可以在不断开连接的前提下取消某个 request 的 stream，表现更好。

- 请求优先级设置

- 流量控制

  
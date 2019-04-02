## WebSocket

WebSocket 是建立在TCP协议上的一种全双工网路通信协议。

它支持服务端推送消息至客户端。

传统的CS模式是浏览器端不断轮询请求服务端，服务端收到请求后将请求结果推送至客户端。



WebSocket只需要建立一次TCP连接，CS就可以持久性全双工通信，并进行双向通信

WebSocket 是独立的、创建在 TCP 上的协议。

Websocket 通过[HTTP](https://baike.baidu.com/item/HTTP)/1.1 协议的101状态码进行握手。


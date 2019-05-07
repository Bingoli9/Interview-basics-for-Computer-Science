## spdy

目前支持spdy服务器有netty和nginx  

- spdy增加帧层用于多路复用，多个并发流通过一个TCP连接  
- 多路复用请求：在单个spdy连接能并发的发起请求，并不限制请求数
- 请求优先级：客户端能请求某个资源被优先传输 这避免高优先级请求被非关键资源堵塞网络通道的问题  
- 头部压缩：客户端现在发送大量冗余HTTP头部信息
- 服务端推送流：服务端能向客户端推送数据不需要客户端发起一个请求

spdy改动的是http协议，改动http只需要更新browser和web server，而改动tcp/ip困难，需要更新巨量路由器，服务器和客户端操作系统  


<center>
<img src="https://raw.githubusercontent.com/zqjflash/spdy-browser/master/SPDY.png"/>
</center>

#### spdy文档结构

Spdy分为两层：Framing Layer和Http layer Framing Layer位于tcp协议层之上，传输的数据单元是frame，同一个TCP连接可以  
传输多个独立的frame。 HTTP Layer则位于Framing Layer之上，负责吧HTTP协议于SPDY协议的转换  


- Session层作用：在一个单独的TCP连接上传输多个有序的frame，一个session与一个TCP连接一一对应 Session概念等同于  
framing layer。为了最好的性能，spdy期望客户端不要关闭连接直到用户离开这个连接引用的所有页面，或者直到服务端关闭  连接。服务端鼓励尽可能长的打开连接，但是，如果需要，能终止连接，当任何一段关闭连接，必须首先发送GOAWAY帧，这样  断点就能确定在关闭连接前完成的请求  


- Session层整个网络连接链路位置如图：

<center>
<img src="https://raw.githubusercontent.com/zqjflash/spdy-browser/master/spdy_session.png"/>
</center>


- frame
一旦连接建立，客户端和服务端交换帧消息。分为两类：Control frame和Data Frame  

- stream：由多个相关的frame组成。一个stream只能用于传输一次HTTP请求以及该请求对应的HTTP响应  


- 子资源push时序图  
<center>
    <img src="https://raw.githubusercontent.com/zqjflash/spdy-browser/master/spdy_sub_push.png"/>
</center>

- 预连接和连接池
为了减少连接建立带来的额外消耗，采用预连接策略，处理流程，同时，在网络不稳定情况下，TCP拥塞算法会直接减缓资源的下载速度  




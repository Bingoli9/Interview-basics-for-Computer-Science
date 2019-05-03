## http establish optimization


http 连接优化需解决两个核心问题：  
- 连接建立耗时较长
- 连接建立可能失败，导致成功率下降，进而影响用户体验


### TLS连接优化

需要服务端和客户端同时支持，共同完成优化手段，包括Session Resumption 和 False Start

#### Session Resumption

<center>
    <img src="https://mmbiz.qpic.cn/mmbiz_png/Ce6bSqXkduzBwqfVkDTFNauYXfIkSdtJTmg5Tia6apXNticCVI5vHNQ4nqYkTWXEounia0zTdibOFTWyD33R1ZB46Q/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1"/>
</center>

- Session Identifier
Session Identifier中文为会话标识符，更像我们熟知的session的概念。是 TLS 握手中生成的 Session ID。服务端会将Session ID保存起来，客户端也会存储Session ID，在后续的ClientHello中带上它，服务端如果能找到匹配的信息，就可以完成一次快速握手。
- Session Ticket




#### TCP连接优化






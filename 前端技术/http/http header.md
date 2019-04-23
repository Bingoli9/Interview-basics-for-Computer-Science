## http header

For Http1.1

#### Request_header

- Accept

- Accept-Charset

- Accept-Encoding

- Accept_Language

- Host

- if-Match

  客户端通过if-Matcher来检查etag

- if-Modified-Since

  当服务器发送last-modified时间之后，再次请求，需要带上这个header，如果服务器判断相同，则返回304，不同则返回200

- if-None-Matcher

- Max-Forwards

  必须在使用trace method的时候，带上，浏览器不用测试

  限制代理数和网关数

- Proxy-Authrozation

  向代理服务器使用

- Range

  客户端请求部分下载用的

- Refer

  记录上一步url

- User-Agent

  指明浏览器版本

#### Response Header

- Age

  服务器通知客户端再次刷新时间

- Location

  如果返回20X并且带上location，则不跳转，但是可以获取

  如果返回30X并且带上resource，则必须自动跳转

- Proxy-Authenticate

- public

  向客户端指明服务器可用的方法集合，比如head，trace，get，put

- Retry-After

  告诉客户端多少时间之后retry，并同时返回503错误

- Server

  返回服务器软件版本之类的

  

#### Entity Header

- Allow

  服务器通知客户端支持的请求方法

- Authorization

- Content-Base

  制定base url

- Content-Encoding

- Content-Language

- Content-Length

- Content-Location

  重定向地址

- Content-MD5

- Content-Range

  一般用于断点续传

- Content-Type

  实体内容类型

- Date

- ETag

  服务器第一次将etag发送给客户端，再次请求时，浏览器需要将etag带给服务端。如果相同，返回304，不同，则返回200和新内容。

- Expires

  刷新时，定义页面过期时间，在该时间内，返回304。

  

#### General Header

- Cache-Control

- Connection

  specify options that are desired for that particular connection and MUST NOT be communicated by proxies over futher connections

- Pragma

  pragma指令对所有协议请求链上都有小

  比如pragma:nocahce则所有路由上的设备都不能cache

- Transfer-Encoding

  制定传输的消息编码

- Upgrade

  客户端发送upgrade，并制定其他通讯协议，如果服务器支持，则必须返回101 Upgrade: HTTP/2.0, SHTTP/1.3, IRC/6.9, RTA/x11

  
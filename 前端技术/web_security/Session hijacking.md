## Session hijacking

The Session Hijacking attack consists of the exploitation of the web session cntrol mechanism, which is normally managed for a session token.

Because http communication uses many different TCP connections, the web server needs a method to recognize every user's connections. The most usefil method depends on a token that the Web Server sends to the client browser after a successful client authentication. A session token is normally composed of a string of variable width and it could be used in different ways, like in the URL, in the header of the http requistion as a cookie, in orther parts of the header of the http request, or yet in the body of the http requisiton.



The Session Hijacking attack compromises the session token by stealing or predicting a valid session token to gain unauthorized access to the Web Server.



#### 攻击方式

- 预测会话token
- 会话嗅探
- 客户端攻击
- 中间人攻击
- Man-in-the-browser attack


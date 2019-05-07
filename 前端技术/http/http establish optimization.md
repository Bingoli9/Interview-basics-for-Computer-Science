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
Session Identifier中文为会话标识符，更像我们熟知的session的概念。是 TLS 握手中生成的 Session   ID。服务端会将Session ID保存起来，客户端也会存储Session ID，在后续的ClientHello中带上它，服务端如果能找到匹配的信息，就可以完成一次快速握手。
- Session Ticket
Session Identifier存在一些弊端，比如客户端多次请求如果没有落在同一台机器上就无法找到匹配的信息，但Session Ticket可以。Session Ticket更像我们熟知的cookie的概念，Session Ticket用只有服务端知道的安全密钥加密过的会话信息，保存在客户端上。客户端在ClientHello时带上了Session Ticket，服务器如果能成功解密就可以完成快速握手。

Session Identifier 以及 Session Ticket存在时效性问题，不是永久生效的。这两种法方法可以省去TLS握手过程中证书下载，密钥协商交换环街，节省1个RTT时间

#### False Start
<center>
    <img src="https://mmbiz.qpic.cn/mmbiz_png/Ce6bSqXkduzBwqfVkDTFNauYXfIkSdtJyAehTeibRkwTsbv3D5XIicouHVfH7x7zYVzkGBobn0ZcyQXVL7ericebw/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1"/>
</center>

TLS第一步握手成功之后，客户端发送Change Cipher Spec Finished的同时开始数据传输，服务端在TLS握手完成时直接返回应用数据。应用数据的发送实际上并未等到握手全部完成，所以称之为抢跑  

从结果看省去了1个RTT的时间。False Start有两个前提条件，一是要通过应用层协议协商ALPN（Application Layer Protocol Negotiation）握手，二是要支持前向安全的加密算法。  


#### TCP连接优化


- 连接池

<center>
    <img src="https://mmbiz.qpic.cn/mmbiz_png/Ce6bSqXkduzBwqfVkDTFNauYXfIkSdtJOBtTqDuAZJgOU7ftOV6MSqRjgicVNfVXbTzyQ6YxiafysDJuQdcXLBiag/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1"/>
</center>

- 不同类型连接池以组合形式互相复用能力

- 预连接
<center>
 <img src="https://mmbiz.qpic.cn/mmbiz_png/Ce6bSqXkduzBwqfVkDTFNauYXfIkSdtJmvC0hn8EjGw7qiaiatNf6Xyrt0r0qRDBDwtFK4Gmk9gibmcda3YaiaT3oQ/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1"/>
</center>
 - 针对核心业务预连接
 - 采用域名 + 连接数方式； http 1.x下单域名有连接数限制； http2.x单域名仅有一条连接
 - 预连接建立：在网络库初始化的时候，延迟5秒预连接，主要考虑冷启动影响
 - 预连接保持：网络库初始化时候，除了预连接建立，还创建预连接定时器，根据使用者的配置重新建立连接
 
- 连接重建
连接重建，将连接重新建立。解决场景是App网络状态变化，IP地址变化，导致连接不可用  
 - 在网络状态变化时，第一步会清除掉连接池里的idle socket。对于从未使用过的空闲socket超过60秒清除，对于使用过的空闲socket超过90s清除； 然后重建连接需要等待200ms，目的是等待DNS先重建完成  
 - 处于性能考虑，连接重建的连接个数限制是100个

- 备用连接
预备连接，它解决掉场景是正常发送一个请求当group内无连接可用的时候。group是管理socket的最小单元，内部包含活跃socket，空闲socket，连接任务，等待请求）。  

当有请求来临时，连接池内无连接可用，会启动定时器开启备用连接，定时器的间隔时间时250ms，与主连接进行竞争，如果主连接因为网络抖动或者网络状态不好，导致连接失败，那么备用连接就直接发送请求。如果主连接成功，那么备用连接就被取消  

在连接池无连接的情况下，务必要创建连接的，在主连接之外加一个备用连接，会大大提升创建连接的成功率，从而提升用户体验  

#### 复合连接
它解决场景是为了多个IP地址连接选取问题  

复合连接针对所有请求  

DNS查询一般返回多个IP地址，


- 如果结果存在IPV6地址，那么优先选用IPV6地址
- 多个ip地址顺序尝试建立连接，若果第一IP返回失败，将立即开启连接第二个IP
- 如果第一个IP率先返回成功，那么第二个ip将加入连接尝试列表并停止所有尝试连接
- 如果第一个ip失败，会立刻开始第二个ip连接
- 如果第一个ip吃鱼pending状态，那么会启动一个定时器，默认延迟2s或发起第二个ip连接，如果多个ip，则递归连接。不同网络制式延迟时间不一样，这样体验会更好一点。

复合连接目的是提供最有IP选取禁止，但也会带来服务端高负载，需要进行综合评估  




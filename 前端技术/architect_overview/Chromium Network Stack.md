## Chromium Network Stack

The network process is single thread and multi-platform network library, which mainly used to request network resource.

There are two main module: URLRequest and URLRequest.

URLRequestContext includes cookies, proxy parser, cache and so on.

Multiple URLRequest object can share one URLRequestContext. 



#### Code Structure

- Net/base network application, including cookie, network observation, SSL and so on
- net/disk_cache: web resources cache
- Net/ftp: FTP
- Net/http
- Net/ocsp
- Net/proxy: Proxy setting, proxy parsing and script extractaion
- Net/quic: QUIC
- net/socket: TCP socket, SSL socket and socket pool
- net/socket_stream: WebSockers socket stream
- Net/spdy: HTTP2 and SPDY implementation
- net/url_request: URLRequest, URLRequestContext and URLRequestJob implementaion
- Net/websockets: WebSocket implementation



#### HTTP Network Request Diagram

<center>
  <img src = "https://upload-images.jianshu.io/upload_images/3768281-78cf6b9a51d321f4.jpg" />
</center>



#### URLRequest

```C++
class URLRequest {
 public:
  // Construct a URLRequest for |url|, notifying events to |delegate|.
  URLRequest(const GURL& url, Delegate* delegate);
  
  // Specify the shared state
  void set_context(URLRequestContext* context);
 
  // Start the request. Notifications will be sent to |delegate|.
  void Start();
 
  // Read data from the request.
  bool Read(IOBuffer* buf, int max_bytes, int* bytes_read);
};
 
class URLRequest::Delegate {
 public:
  // Called after the response has started coming in or an error occurred.
  virtual void OnResponseStarted(...) = 0;
 
  // Called when Read() calls complete.
  virtual void OnReadCompleted(...) = 0;
};

```

#### URLRequestHttpJob

Steps:

- URLRequestHttpJob first search the cookie info asychronously or synchronously. 
- HttpTransactionFactory -> HttpTransaction. Usually, the HttpCache is assigned as HttpTransactionFactory.
- HttpNetworkTransaction will own the HttpNetworkSession object to maintain the context of HTTP request.

#### HttpNetworkTransaction

```C++
class HttpNetworkSession {
 private:
  // Shim so we can mock out ClientSockets.
  ClientSocketFactory* const socket_factory_;
  // Pointer to URLRequestContext's HostResolver.
  HostResolver* const host_resolver_;
  // Reference to URLRequestContext's ProxyService
  scoped_refptr<ProxyService> proxy_service_;
  // Contains all the socket pools.
  ClientSocketPoolManager socket_pool_manager_;
  // Contains the active SpdySessions.
  scoped_ptr<SpdySessionPool> spdy_session_pool_;
  // Handles HttpStream creation.
  HttpStreamFactory http_stream_factory_;
};
```

HttpNetworkTransaction need HttpStreamFactory to create a HttpStram object. HttpStreamRequest need to handle the connect logic, and once the connection is built, need a HttpStream child class to wrapper it, and manage the network connection.

```C++
class HttpStream {
 public:
  virtual int SendRequest(...) = 0;
  virtual int ReadResponseHeaders(...) = 0;
  virtual int ReadResponseBody(...) = 0;
  ...
};
```



#### HttpStreamFactory

- HttpStreamFactory will first run the proxy parsing to decide wether need the proxy or not.
- HttpStreamFactory will check whether the SpdySessionPool offers the SpdySession or not. If not, will request socket from socket pool
- If the socket is SSL socket, it will check NPN or SPDY
- As for the SPDY, use the spdySession, and create the SpdyStream
- As for the HTTP, will wrapper socket in HttpBasicStream

#### Proxy Parsing

HttpStreamFactory search the ProxyService to return the ProxyInfo.

- check newest proxy setting
- If no proxy setting, it will check the current proxy setting with ProxyConfigService
- Use PAC script to decide the proper proxy (or lack the proxy)
- If no PAC script, will use WPAD auto check or assign specific PAC URL and use ProxyScriptFetcher to get the PAC script
- parse the PAC script with ProxyResolver

#### Host Parsing

TCP connection need host parsing except TCP hand-shake. It will use block function call HostResolverImpl::getaddrinfo()

Usually, host parsing will involve DNS parsing.

#### Connection Manage



#### SSL/TLS

Using libssl of NSS to handle SLL connnection logic.


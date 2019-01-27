## Socket 

#### socket()函数

```C++
int socket(int domain, int type, int protocol)		
    # domain:protocol domain, including AF_INET、AF_INET6、AF_LOCAL、AF_ROUTE等
    # type: socket type，including SOCK_STREAM SOCK_DGRAM SOCK_RAW SOCK_SEQPACKET
    # protocol:
```

#### bind()

Bind the socket and local protocol address

```C++
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

#### listen()

```C++
int listen(int sockfd, int backlog);
```

listen() function mainly deal with two things:

- transform initiactive socket into passive socket
- the parameter backlog define the max queue capacity

#### connect()

```C++
int connect(int sockfd, const struct sockaddr *addr, socklen_t addlen);
```

#### accept()

```C++
int accept(int sockfd, struct aockaddr *addr, socklen_t *addrlen);
```

#### close()

```C++
int close(int fd);
```

close() is used for close the socket and terminate the TCP connection

close() deduct the reference amount of socket by one. Until the reference amount is zero, will it toogle the terminate request.

#### shutdown

```C++
int shuntdown(int sockfd, int howto)
```

SHUT_RD: socket can't write but can read

SHUT_WR: socket can't rean but can write


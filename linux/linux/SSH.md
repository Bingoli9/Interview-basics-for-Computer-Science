## SSH

SSH service is a daemon that has the system backend monitoring the client connection. The process of SSH server is called SSHD, which responsible for real-time monitoring the client request, including the exchange of public secret keys and other information.

The SSH service terminal consists of two parts: openssh and openssl

### SSH  encrpytion technique

DSA: digital signature algorithm

RSA: digital signature and encrpytion

### sftp

```C++
sftp -oPort=22 root@192.168.25.137
    put /etc/hosts /tmp
    get /etc/hosts /home/omd
```

### scp

```C++
scp localfile liqining@192.168.1.181:/home/liqining/
```


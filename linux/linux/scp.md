### scp/sftp

本地网络跟远程网络进行数据交互， 或者数据迁移，常用的有三种方法：
- ftp
- wget、fetch
- rysync

### scp
scp -P port user@serverip:/home/user/filename /home/user/filename

### 从本地复制到远程
scp local_file remote_username@remote_ip:remote_folder
scp local_file remote_ip:remote_folder



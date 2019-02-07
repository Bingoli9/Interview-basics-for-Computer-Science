## fcntl

"function": manipulate file descriptor    
"synopsis": int fcntl(int fd, int cmd, .../* arg */);  
"description": fcnt() performs one of the operations described below on the open file descriptor fd.  
The operation is determined by cmd.
"example":
add file's flag, suppose the file is block, and you want to set it non-block:
```C++
flags = fcntl(fd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(fd,F_SETFL,flags);
```
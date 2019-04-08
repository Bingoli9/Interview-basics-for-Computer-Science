## Chromium Debug

##### Java Dubug

<center>
  <img src = "http://img.blog.csdn.net/20140516172945093?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbWlsYWRvX25qdQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center"/>
</center>

Use adb to communicate devices. 

Adb host daemon is the backend process in devices, using adb will trigger the host daemon process.

#### C/C++ Debug

Use GDB and ADB

<center>
  <img src = "http://img.blog.csdn.net/20140516173013921?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbWlsYWRvX25qdQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center"/>
</center>

Use GdbService to help debugging. Gdb is included in NDK and need to run in android devices. 

Need ADB port forwarding technique, and using this technique will communicate with gdbservice.

#### Other Debugg

- Logging

- Tombstome

  A crash watcher tools. Use Tombstome can trace the carsh infomation.

  


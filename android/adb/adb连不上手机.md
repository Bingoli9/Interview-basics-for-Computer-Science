## adb 连不上手机
### 方案一

adb kill-server  
adb start-server  


### 方案二
- vim  ~/.android/adb_usb.ini  
- lsusb 查找手机VID  
- 在adb_usb.ini中添加VID  
- 重启adb server  




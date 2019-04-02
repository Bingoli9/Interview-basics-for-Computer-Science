## adb

Android Debug Bridge

adb工作方式采用监听Socket TCP 5554等端口的方式

借助adb，可以管理设备或手机模拟器的状态。还可以进行手机很多操作，如安装软件，系统升级，运行shell命令等。adb是Android手机和PC端桥梁，可以让用户在电脑上对手机进行全面的操作

#### 显示系统中全部Android平台

```C++
android list targets
```

#### Show AVD

android list avd

#### Create AVD

android create avd —name ** —target platform number

#### Start AVD

emulator -avd name -sdcard ~/name.img

#### Create SDCard

mksdcard 1024M ~/name.img

#### AVD location

Linux: ~/.android/avd

#### Start DDMS

ddms

#### show runnimg AVD

adb devices

#### Command AVD

adb -s AVD_Number COMMAND

#### Install Apk

app install -r NAME.apk

### AVD Shell

adb shell

#### AVD SDK

android

#### Remove apk

adb shell

cd data/app

rm apk

exit

adb uninstall apk

adb install -r apk

#### Get Root

adb root

#### Start Activity

adb shell am start -n PACKAGE CLASS

#### Expose port

adb forward tcp:5555 tcp:80000
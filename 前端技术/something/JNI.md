## JNI

JNI: java native interface. JNI is a ptotocol used for communication between java code and extern native code(c/c++);

#### basic type correlation among c, java and jni

<center>
  <img src = "https://images2015.cnblogs.com/blog/740688/201510/740688-20151019200156739-1770160850.png"/>
</center>



#### Cross-Compile

Cross-Compile is that in a platform, we compile the binary code which can run on other type's platform.

#### NDK

Native Development Kit, a tool which used for design JNI.

#### example

好了，准备知识已经完毕，下面开始我们的一个JNI例子。

​        1、新建一个Android项目，在根目录下创建 jni文件夹，用于存放 C源码。

​        2、在java代码中，创建一个本地方法 getStringFromC 本地方法没有方法体。

1. ```
   private native String getStringFromC();
   ```

   3、在jni中创建一个C文件，定义一个函数实现本地方法，函数名必须用使用 本地方法的全类名，点改为下划线。

```
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
//方法名必须为本地方法的全类名点改为下划线，穿入的两个参数必须这样写，
//第一个参数为Java虚拟机的内存地址的二级指针，用于本地方法与java虚拟机在内存中交互
//第二个参数为一个java对象，即是哪个对象调用了这个 c方法
jstring Java_com_mwp_jnihelloworld_MainActivity_getStringFromC(JNIEnv* env,
                                                               jobject obj){
    //定义一个C语言字符串
    char* cstr = "hello form c";
    //返回值是java字符串，所以要将C语言的字符串转换成java的字符串
    //在jni.h 中定义了字符串转换函数的函数指针
    //jstring   (*NewStringUTF)(JNIEnv*, const char*);
    //第一种方法：很少用
    jstring jstr1 = (*(*env)).NewStringUTF(env, cstr);
    //第二种方法，推荐
    jstring jstr2 = (*env) -> NewStringUTF(env, cstr);
    return jstr2;
}
```

​        4、在jni中创建 Android.mk文件，用于配置 本地方法

```
 LOCAL_PATH := $(call my-dir)
    include $(CLEAR_VARS)
    #编译生成的文件的类库叫什么名字
    LOCAL_MODULE    := hello
    #要编译的c文件
    LOCAL_SRC_FILES := Hello.c
    include $(BUILD_SHARED_LIBRARY)
```

​         5、在jni目录下执行 ndk-build.cmd指令，编译c文件

​         6、在java代码中加载编译后生成的so类库，调用本地方法，将项目部署到虚拟机上之后就会发现toast弹出的C代码定义的字符串，第一个例子执行成功了。

```
static{
        //加载打包完毕的 so类库
        System.loadLibrary("hello");
    }
```

​         7、jni打包的C语言类库默认仅支持 arm架构，需要在jni目录下创建 Android.mk 文件添加如下代码可以支持x86架构

1. ```
   APP_ABI := armeabi armeabi-v7a x86
   ```
## Android C++ and Java 调用

#### C++调用Java

通过c++中的jniEnv的几个关键API实现C++中调用Java方法

在Java中：

```C++
package com.duicky;
public class TestProvider {
 
public static String getTime() {
        LogUtils.printWithSystemOut( "Call From C Java Static Method"   );
        LogUtils.toastMessage(MainActivity.mContext, "Call From C Java Static Method"   );
        return String.valueOf(System.currentTimeMillis());
}
 
public void sayHello(String msg) {
        LogUtils.printWithSystemOut("Call From C Java Not Static Method ：" + msg);
        LogUtils.toastMessage(MainActivity.mContext, "Call From C Java Not Static Method ：" + msg);
}
 
}
```

对于这样一个Java层的类， 在C++中实现调用它的静态方法和普通方法需要定义其映射的类、对象, 和方法.

```
jclass TestProvider;
jobject mTestProvider;
jmethodID getTime;
jmethodID sayHello;
```

对这几个对象的赋值:

```
jclass TestProvider = (*jniEnv)->FindClass(jniEnv,"com/duicky/TestProvider");
TestProvider mTestProvider = (*jniEnv)->NewObject(jniEnv, TestProvider,construction_id);
jmethodID getTime = (*jniEnv)->GetStaticMethodID(jniEnv, TestProvider, "getTime","()Ljava/lang/String;"); //都是通过类找到方法
jmethodID sayHello = (*jniEnv)->GetMethodID(jniEnv, TestProvider, "sayHello","(Ljava/lang/String;)V"); //都是通过类找到方法
```

#### Java 调用C++

Java类中写一个native关键字修饰的方法, 通过javah生成一个函数名,
命名规范是: 包名*类名*方法名. 在C++中对这个函数进行实现.
这样Java层调用这个native方法就进入到了C++中的实现中去了.
例如:

```
private native void nativeSaveWebArchieve(long nativeTabAndroid, String filename, ValueCallback<String> callback);
```

#### chromium

chromium为方便JNI的开发, 写了一个关键脚本: jni_generator.py,
在编译前扫描所有的java文件, 对java文件中有@CalledByNative注解的方法和native关键字修饰的方法,
在out/release/gen/目录下生成和java文件对应的.h文件，
命名规则是: 类名_jni.h, 例如: Tab.java对应Tab_jni.h, TraceEvent.java对应TraceEvent_jni.h

以Tab.java为例:

```
public class Tab {
    //内核获得用户输入的url
    @CalledByNative
    public String getUrl() {
        String url = getWebContents() != null && !getWebContents().isDestroyed() ? getWebContents().getUrl() : "";
        if (getContentViewCore() != null || getNativePage() != null || !TextUtils.isEmpty(url)) {
            mUrl = url;
        }

        return mUrl != null ? mUrl : "";
    }

    //保存网页的API
    private native void nativeSaveWebArchieve(long nativeTabAndroid, String filename, ValueCallback<String> callback);
}
```

对应着Tab_jni.h中的内容:

```
//生成一个方法对调用Java中的方法进行封装
//本质还是: 通过JNIEnv找到method id, 然后通过CallObjectMethod() 进行调用.
static base::android::ScopedJavaLocalRef<jstring> Java_Tab_getUrl(JNIEnv* env,
    jobject obj) {
  /* Must call RegisterNativesImpl()  */
  CHECK_CLAZZ(env, obj,
      Tab_clazz(env), NULL);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_INSTANCE>(
      env, Tab_clazz(env),
      "getUrl",

"("
")"
"Ljava/lang/String;",
      &g_Tab_getUrl);

  jstring ret =
      static_cast<jstring>(env->CallObjectMethod(obj, //***这里实现的真正调用java中的方法***
          method_id));
  jni_generator::CheckException(env);
  return base::android::ScopedJavaLocalRef<jstring>(env, ret);
}
```

对java中的native方法进行实现，
方法名必须按照: 包名*类名*方法名， 符合签名规范.

```
void Java_org_chromium_chrome_browser_Tab_nativeSaveWebArchieve(JNIEnv* env,
    jobject jcaller,
    jlong nativeTabAndroid,
    jstring filename,
    jobject callback) {
  TabAndroid* native = reinterpret_cast<TabAndroid*>(nativeTabAndroid);
  CHECK_NATIVE_PTR(env, jcaller, native, "SaveWebArchieve");
  return native->SaveWebArchieve(env, jcaller, filename, callback);
}
```

在tab_android.cc中 #include "jni/Tab_jni.h"

```
#include "jni/Tab_jni.h"
GURL TabAndroid::GetURL() const {
  JNIEnv* env = base::android::AttachCurrentThread();
  return GURL(base::android::ConvertJavaStringToUTF8(
      Java_Tab_getUrl(env, weak_java_tab_.get(env).obj())));
}


void TabAndroid::SaveWebArchieve(JNIEnv *env, jobject obj, jstring path, jobject callback) {
    ScopedJavaGlobalRef<jobject>* j_callback = new ScopedJavaGlobalRef<jobject>();
    j_callback->Reset(env, callback);
    base::FilePath target_path(ConvertJavaStringToUTF8(env, path));
    web_contents()->GenerateMHTML(
      target_path,
      base::Bind(&GenerateMHTMLCallback, base::Owned(j_callback), target_path));
}
```
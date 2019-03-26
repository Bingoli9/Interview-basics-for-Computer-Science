## Chromium Delegate Pattern

什么是委托模式？

根据维基百科的解释，委托模式就是在面向对象的编程中，某些类自己不执行一些任务，并把这些任务委托给另外一个类去执行，那么执行任务的类就被称为委托类。

```C++
class RealPrinter { // the "delegate"
     void print() {
       System.out.print("something");
     }
 }
 class Printer { // the "delegator"
     RealPrinter p = new RealPrinter(); // create the delegate
     void print() {
       p.print(); // delegation
     }
 }
 public class Main {
    public static void main(String[] args) {
         Printer printer = new Printer();
         printer.print();
     }
 }
```

#### 委托模式在Chromium中的应用

随着Chromium开源项目的发展，基于它开发的软件也越来越多，除了流行的Chrome浏览器之外，还有Content Shell，CEF3，Android WebView（Android4.4以后）和Crosswalk等，这些程序除了公用的网页渲染和JavaScript执行外，每款软件都有自身的特定需求，那么Chromium如何能实现开发者灵活定制的需求呢？这里Chromium在设计时采用的Delegate模式应该发挥了重要的作用。从源码分析来看，每个模块具体功能的实现基本上都是通过Delegate类来实现的，如果开发者继承该Delegate类，并加以实现就能很方便的完成定制，倘若开发者不需要某个模块的功能，也就不用实现相关的Delegate类，那么该模块就不会发挥效用。

另外，这里需要提到Chromium项目中自动测试架构，它的设计也得益于委托模式。这些测试能直接检测Chromium中的某个特性或功能能不能正常工作，检查新添加的代码对原有的代码有没有影响，其重要性就不言而喻了，但是由于有些功能需要手动干预才能正常工作，比如下载模块中弹出的对话框需要手动选择保存文件的地址和文件名；getUserMedia功能需要用户手动选择允许或禁止访问摄像头或麦克风等等，这些会给自动测试代码麻烦，但是有了Delegate的设计就可以很方便的避开这些问题，开发者只需要设计一下新的TestDelegate类，来继承那些已经正常工作的Delegate类，并对该类做一些简单的修改事先填好一些数据，从而绕开需要手动输入代码块的执行。这就一方面完成了对已有代码的测试，也同时兼具了自动化。





下面以下载模块举例说明

在Chromium项目中有个DownloadManager类，它负责完成任务的下载功能，当在浏览器中点击某个不能被渲染的链接时，浏览器就认为该链接的文件需要下载，就通过DownloadManager来完成下载流程。但是下载文件的实际工作都是在DownloadManagerDelegate中完成的，比如选择文件的路径，检查文件路径名是否合法等。

代码片段如下：

```C++
class DownloadManager{
public:
// 开发者可基于DownloadManagerDelegate派生出新的委托类，并通过该函数进行注册。
virtual void SetDelegate(DownloadManagerDelegate* delegate);
// 如果获取Delegate类为Null的话，表明下载模块未启用。
virtual DownloadManagerDelegate* GetDelegate() const;
private:
DownloadManagerDelegate  *delegate_;
};
Class DownloadManagerDelegate{
//弹出对话框，让用户选择保存路径。
void ChooseSavePath(….);
void Shutdown(…);
……
};
```


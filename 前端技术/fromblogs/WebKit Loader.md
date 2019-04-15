WebKit Loader

Loader modules includes Frameloader, DocumentLoader and MainResourceLoader. The Webkit module involved in loaing is page, loader and platform.

<center>
  @<img src = "1353405724_1675.jpg"/>
</center>



<center>
  @<img src = "1353405899_9330.jpg"/>
</center>

FrameTree对象用来协助管理父帧和子帧的关系。

NavigationScheduler对象用来管理页面跳转调度（比如重定向，meta refresh等）。

DOMWindow用来管理同DOM相关的事件、属性和消息。

FrameView用于Frame的排版。

Document用于管理DOM节点。

EventHandle是事件的处理对象，主要是同上层应用也就是用户参与的事件的处理。

一个Frame包含一个FrameLoader作为加载的最主要的负责对象。

SubFrameLoader负责子Frame的加载

DocumentWriter负责加载结束之后的数据处理

FrameLoaderStateMachine维护FrameLoader的状态

PolicyChecker主要用来对FrameLoader进行一些校验

ResourceLoadNotifier主要用于同ResourceLoader及FrameLoaderClient打交道（可以理解为 ResourceLoader有事件变化或者发生的时候，通知FrameLoader的一个手段）



#### Network module in load

<center>
  @<img src = "1353406092_2900.jpg"/>
</center>



#### Loading flow

1. ​    *DocumentLoader* 调用 *MainResourceLoader::load* 向 *loader* 发起请求

*2.*        调用 *MainResourceLoader::loadNow*

*3.*        调用 *MainResourceLoader::willSendRequest*

*4.*        调用 *ResourceLoader::willSendRequest,* 将 *callback* 通过 *ResourceNotifier* 传导给 *FrameLoaderClient* 。 *Client* 可以在回调中操作 *ResourceRequest* ，比如设置请求头部。

*5.*        调用 *PolicyChecker::checkNavigationPolicy* 过滤掉重复请求等

*6.*        *loader* 调用 *ResourceHandle::create* 向 *Network* 发起加载请求

*7.*        收到第一个 *HTTP* 响应数据包 *,Network* 回调*MainResourceLoader::didReceiveResponse* ，主要处理 *HTTP* 头部。

*8.*        调用 *PolicyChecker::* *checkContentPolicy,* 并最终通过 *FrameLoaderClient* 的*dispatchDecidePolicyForMIMEType* 判断是否为下载请求（存在 *"Content-Disposition"http* 头部）

*9.*        调用 *MainResourceLoader::continueAfterContentPolicy* ，根据*ResourceResponse* 检测是否发生错误。

*10.*   调用 *ResourceLoader::didReceiveResponse* ，将 *callback* 通过 *ResourceNotifier*传导给 *FrameLoaderClient* 。

*11.*   收到 *HTTP* 体部数据，调用 *MainResourceLoader::didReceiveData*

*12.*   调用 *ResourceLoader::didReceiveData* ，将 *callback* 通过 *ResourceNotifier* 传导给 *FrameLoaderClient*

*13.*   调用 *MainResourceLoader::addData*

*14.*   调用 *DocumentLoader::receivedData*

*15.*   调用 *DocumentLoader::commitLoad*

*16.*   调用 *FrameLoader::commitProvisionalLoad* ， *FrameLoader* 从 *provisional* 状态跃迁到 *Committed* 状态

*17.*   调用 *FrameLoaderClientQt::committedLoad*

*18.*   调用 *DocumentLoader::commitData* ，启动 *Writer* 对象来处理数据（*DocumentWriter::setEncoding* ， *DocumentWriter::addData* ）

*19.*   调用 *DocumentWriter::addData*

*20.*   调用 *DocumentParser::appendByte*

*21.*   调用 *DecodedDataDocumentParser::appendBytes* 对文本编码进行解码

*22.*   调用 *HTMLDocumentParser::append* ，进行 *HTML* 解析
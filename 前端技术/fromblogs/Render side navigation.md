## Render side navigation



<center>
  @<img src = "20170803103856686"/>
</center>



Navigation主要在Render进程完成，关键入口是Blink::FrameLoader。

- FrameLoader::load()
- 创建Blink::DocumentLoader
- 通过Blink::ResourceFetcher获取主资源加载
- Blink::ResourceLoader
- WebUrlLoaderImpl
- ResourceDispathcer发送IPC消息，请求发送到Browser进程的ResourceDispatcherHostImpl
- ResourceDispatcherHostImpl创建net::URLRequest
- net模块进行网络资源加载
- 完成之后原路返回至Blink::DocumentLoader解析渲染
- 通知Browser进程navigation的commit的结束
- browser进程NavigaitonController会commit本次NavigationEntry
- RenderFrameHostManager调度出pending状态的RenderFrameHost
- browser加载document到frame，完成整个navigation



具体流程

<center>
  @<img src = "20170803110953165"/>
</center>


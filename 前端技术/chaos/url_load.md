## URL加载

## 第一阶段（发送请求）
### WebContents
 
### NavigationController
NavigationController对象URL的前进/后退列表，负责加载URL到WebContents中  

成员函数LoadURLWithParams方法被调用后，需要经过url判断，然后调用成员函数  
NavigationWithoutEntry方法继续处理，该函数主要做了三件事：  
- 确定URL所要加载在FrameTree中哪个node上，即得到FrameTreeNode对象
- 创建NavigationEntry对象，用于组建NavigationRequest
- 输送NavigationRequest到目标FrameTreeNode的Navigator对象的Navigate方法中

### Navigator
Navigator负责在FrameTree的节点中执行URL导航操作，可以被同一棵FrameTree上的  
多个FrameTreeNode所共享。  
成员函数Navigate主要做的事情是：
- 先判断当前指定的FrameTreeNode所代表的网页是否有悬挂的BeforeUnload事件处理器  
需要执行，如果有，则先执行
- 派发NavigationRequest到FrameTreeNode

### NavigationRequest
NavigationRequest存在于UI线程，确保URL请求会在IO线程中的ResourceDispatcherHost中  
执行，描述UI线程和IO线程之间的交互  

该类先对目标URL进行内容安全策略检查，以及注册各种NavigaitonThrottles对目标URL  
进行审批，最终会创建NavigationURLLoader对象  

### NavigationURLLoader
进行线程调度，在IO线程执行StartWithoutNetworkService方法，并在该方法中调用  
ThrottlingURLLoader::CreateLoaderAndStart()方法创建ThrottlingURLLoader对象  

### ThrottlingURLLoader
类继承与network::mojom::URLLoaderClient，可以进行IPC，且Render进程和Browser进程都有其  
实例化对象  
跟URL加载有关的Throttle用于对网络数据进行拦截过滤处理  

### ResourceDispatcherHost
ResourceDispatcher和ResourceDispatcherHost分别是Render进程和  
Browser进程进行资源分发的接口类  

在BeginNavigationRequest方法中创建URLRequest对象  
在BeginRequestInternal方法中创建ResourceLoader对象  

### ResourceLoader
ResourceLoader集中转发URLRequest、SSLErrorHandler、SSLClientAuthHandler、  
ResourceHandler相关的事件  

该类StartRequestInternal方法汇总，直接调用URLRequest对象的start方法  至此结束  
Navigate的第一个过程  

## 第二阶段 （数据响应）
ResourceLoader类的ResponseCompleted方法被调用，然后通过ResourceLoader成员变量handler的  
OnResponseCompleted方法向上传递数据  

handler可以对数据进行截获处理，最终调用到RenderFrameHostImpl::CommitNavigation，RenderFrameHost  
发送IPC消息到Render进程  

## 第三阶段 （Render进程发起主资源网络请求）
#### RenderFrame
第二阶段CommitNavigation方法除了携带response_header、request_params等基本信息，还有mojom信息相关的  
接口url_loader_client_endpoints和Browser进程目前所支持的URLLoaderFactory列表subresource_loader_factories  
subresource_loader_factories属于bundle，包裹着从Browser进程传递过来的各种URLLoaderFactory  

当进行网络请求时，Render进程去factory列表根据url的schemem里查找对应的URLLoaderFactory，调用他的CreateLoaderAndStart  
方法进行资源请求  

RenderFrameHost通过CommitNavigation发送mojom ipc消息到Render进程中，RenderFrame类的CommitNavigation方法被mojom消息调起  
它根据消息携带的header信息、request参数等信息创建WebURLRequest对象，并调用成员变量frame_的CommitNavigation将其传递过去  
frame_指向WebLocalFrame对象，将其转换成FrameLoadRequest类型，然后调用传递给FreameLoader类的CommitNavigaiton函数  

#### FrameLoader
CommitNavigation接收到FrameLoadRequest后，直接调用StartLoad函数，在StartLoad函数中，创建并用FrameLoadRequest参数初始化  
DocumentLoader对象，然后调用DocumentLoader对象的StartLoading方法  


#### DocumentLoader
StartLoading函数准备好request、fetcher等参数，调用RawRequest类  
的静态方法FetchMainResource去请求主要资源

#### RawResource
FetchMainResource函数，根据Resource::kMainResource类型去创建ResourceFactory对象  同FetchParameters对象  
一起作为参数，调起参数列表中fetcher的RequestResource函数  

#### ResourceFetcher

#### ResourceLoader
Start方法调用ResourceLoaderScheduler::Request，最终回调到  
ResourceLoader的StartWith调用WebURLLoader类LoadAsynchronously  

#### WebURLLoader
LoadAsynchronous通过自己成员变量context_，对request进行加载  最终从  
WebURLLoader::Context::Start方法中调用ResourceDispatcher类的StartAsync  

#### ResourceDispathcer
调用ThrottlingURLLoaderl类的CreateLoaderAndStart方法

#### ThrolltingURLLoader
Start函数接收一个SharedURLLoaderFactory和ResourceRequest参数，调用factory的  
CreateLoaderAndStart方法  

#### ChileURLLoaderactoryBundle
CreateLoaderAndStart方法被调起，参数包含network::ResourceRequest和  
network::mojom::URLLoaderRequest对象，根据request.url获取对应的URLLoaderFactory，  然后调用改factory的CreateLoaderAndStart发送   跨进程ipc消息到Browser Process  

## 第四阶段 （请求主资源）
Browser进程接收CreateLoaderAndStart方法到跨进程调用位置，是在ResourceMessageFilter  
类同名方法CreateLoaderAndStart。最终传递到URLLoaderFactory::  
CreateLoaderAndStart，该方法获取ResourceDispatcherHost实例，调用起OnRequestResourceWithMojo方法，  
代替以前的ResourceHostMsg_RequestResource消息  

ResourceDispatcherHost接收来自Render进程的网络请求相关参数，调用  
OnRequestResourceInternal方法开始对该请求进行加载  

当数据请求有结果时，同样是几个Handler类的OnReaderCompleted方法最先被调用，  
然后通过network::mojom::URLLoaderClinetProxy类的OnStartLoadingResponseBody方法将结果跨进程通知回Render  

## 第五阶段 （接收处理主要资源，发起子资源请求）
















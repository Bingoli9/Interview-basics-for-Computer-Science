## unix socket ipc

chromium unxi socket ipc channel 创建过程

#### 获取channel id
```C++

std::string Channel::GenerateVerifiedChannelID(const std::string& prefix) {
  // A random name is sufficient validation on posix systems, so we don't need
  // an additional shared secret.
 
  std::string id = prefix;
  if (!id.empty())
    id.append(".");
 
  return id.append(GenerateUniqueRandomChannelID());
}
```
#### 创建channel proxy
调用函数ChannelProxy::Create构建Channel Proxy  
传入参数包括
- channel id
- 监听线程 listener
- 监听线程模式：server or client
```C++
coped_ptr<ChannelProxy> ChannelProxy::Create(
    const IPC::ChannelHandle& channel_handle,
    Channel::Mode mode,
    Listener* listener,
    base::SingleThreadTaskRunner* ipc_task_runner) {
  scoped_ptr<ChannelProxy> channel(new ChannelProxy(listener, ipc_task_runner));
  channel->Init(channel_handle, mode, true);
  return channel.Pass();
```

#### ChannelProxy::Context
Context保存发送方和接收方  
ChannelProxy::Contetxt有三类成员需注意：  
- listener_task_runner
当前线程的MessageLoopProxy对象, 通过MessageLoopProxy对象可以向当前线程的  
消息队列发送消息  
- listener
实现listener接口的类可以监听消息  
在chromium多线程模式中，io线程获取到render进程发来的消息后，io线程会转发  
消息至listener指向到对象中  
- ipc_task_runner
与io线程相关联的MessageLoopProxy对象  

#### ChannelProxy初始化
初始化主要创建







